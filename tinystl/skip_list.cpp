/* KTH ACM Contest Template Library
 *
 * tinystl/dictionaries/doubly linked skip list
 *
 * Credit:
 *   Based on paper by William Pugh, CACM, June 1990
 *   Based on standard linked list implementation for KACTL by David Rydh
 *   By Per Austrin
 */

#include "../numerical/pseudo.cpp"
#include "function.cpp"

// ML = MaxLevel, should be roughly $log_{1/p} N$, where $N$ is #elements.
// For $p = 1/2^2$ and $N = 1$ million, this becomes 10. p is determined by pm.
template <class T, class C=less<T>, int ML = 10>
struct skip_list {
  static const int pm = 3; // $p = 1/(pm + 1)$

  struct list_node {
    typedef list_node N;
    T d; int lvl;
    list_node **nxt, **prv;
    list_node(T _d, int _lvl):
      d(_d), lvl(_lvl), nxt(new N*[lvl]), prv(new N*[lvl]) {}
    ~list_node() { delete[] nxt; delete[] prv; }
    void lnk(N* n, int l) { nxt[l] = n; n->prv[l] = this; }
  };

  template <class S>
  struct list_iter {
    typedef list_iter I;
    list_node *p;
    template<class R>
    list_iter(const list_iter<R>& i): p(i.p) {}
    list_iter(list_node *_p): p(_p) {}
    I &operator++() { p = p->nxt[0]; return *this; }
    I &operator--() { p = p->prv[0]; return *this; }
    I operator++(int) { I r(p); p = p->nxt[0]; return r; }
    I operator--(int) { I r(p); p = p->prv[0]; return r; }
    bool operator==(const I &i) const { return p == i.p; }
    bool operator!=(const I &i) const { return p != i.p; }
    S &operator*() const { return p->d; }
    S *operator->() const { return &(p->d); }
  };
  
  typedef T value_type;
  typedef list_node N;
  typedef list_iter<T> iterator;
  typedef list_iter<const T> const_iterator;

  C c;
  list_node *head, *bck[ML];
  int level, n;
  
  void init(const C& _c) {
    c = _c; head = new N(T(), ML); level = n = 0;
    for (int i = 0; i < ML; ++i) head->nxt[i] = head->prv[i] = head;
  }
  
  skip_list(C _c = C()) { init(_c); }
  skip_list(const skip_list& l) { init(l.c); *this = l; }
  virtual ~skip_list() { clear(); delete head; }
  
  skip_list& operator=(const skip_list& l) {
    clear();
    for (const_iterator i = l.begin(); i != l.end(); ++i) insert(*i);
  }

  iterator begin() const { return head->nxt[0]; }
  iterator end() const { return head; }
  
  bool empty() const { return !n; }
  void clear() { while (!empty()) erase(begin()); }
  int size() const { return n; }
  
  iterator find(const T &x, bool left = true) {
    list_node *p = head;
    for (int i = level - 1; i >= 0; --i) {
      while ((p = p->nxt[i]) != head && (left ? c(p->d, x) : !c(x, p->d)));
      bck[i] = p =  p->prv[i];
    }
    if (left) bck[0] = p, p = p->nxt[0];
    return (left ? c(x, p->d) : c(p->d, x)) ? end() : p;
  }
  
  int new_level() { int l = 0; while (++l < ML && !(pseudo() & pm)); return l; }
  
  iterator insert(const T &x, bool multi = true) {
    iterator r(head);
    if ((r = find(x, false)) != end() && !multi) return r;
    r.p = new list_node(x, new_level()); ++n;
    for (int i = level; i < r.p->lvl; ++i) bck[i] = head;
    for (int i = 0; i < r.p->lvl; ++i) {
      r.p->lnk(bck[i]->nxt[i], i);
      bck[i]->lnk(r.p, i);
    }
    if (r.p->lvl > level) level = r.p->lvl;
    return r;
  }
  
  void erase(iterator x) {
    for (int i = 0; i < x.p->lvl; ++i)  x.p->prv[i]->lnk(x.p->nxt[i], i);
    delete x.p, --n;
  }
};

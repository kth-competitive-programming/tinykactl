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
// For $p = 1/2^2$ and $N = 1$ million, this becomes 10. p is determined by pl.
template <class T, class C=less<T>, int ML = 10>
struct skip_list {
  struct list_node {
    T d; int lvl;
    list_node **nxt;
    list_node **prv;
    list_node(int _lvl, T _d = T()):
      d(_d), lvl(_lvl), nxt(new list_node*[lvl]), prv(new list_node*[lvl]) {}
    ~list_node() { delete[] nxt; delete[] prv; }
    void lnk(list_node* n, int l) { nxt[l] = n; n->prv[l] = this; }
  };
  
  template <class TR, class TP>
  struct list_iter {
    typedef list_iter I;
    list_node *p;
    template<class SR, class SP>
    list_iter(const list_iter<SR, SP>& i): p(i.p) {}
    list_iter(list_node *_p): p(_p) {}
    I &operator++() { p = p->nxt[0]; return *this; }
    I &operator--() { p = p->prv[0]; return *this; }
    I operator++(int) { I r(p); p = p->nxt[0]; return r; }
    I operator--(int) { I r(p); p = p->prv[0]; return r; }
    bool operator==(const I &i) const { return p == i.p; }
    bool operator!=(const I &i) const { return p != i.p; }
    TR operator*() const { return p->d; }
    TP operator->() const { return &(p->d); }
  };
  
  typedef T value_type;
  typedef list_iter<T&, T*> iterator;
  typedef list_iter<const T&, const T*> const_iterator;
  static const int pm = 3; // 2^pl - 1, where p = 1/2^pl
  
  C c;
  list_node *head, *bck[ML];
  int level;
  
  skip_list(C _c = C()): c(_c), head(new list_node(ML)), level(0) {
    for (int i = 0; i < ML; ++i)  head->nxt[i] = head->prv[i] = head;
  }
  
  iterator begin() { return head->nxt[0]; }
  const_iterator begin() const { return head->nxt[0]; }
  iterator end() { return head; }
  const_iterator end() const { return head; }
  
  bool empty() const { return begin() == end(); }
  void clear() { while (!empty()) erase(begin()); }
    
  iterator find(const T &x, bool left = true) {
    list_node *p = head;
    for (int i = level - 1; i >= 0; --i) {
      while (p->nxt[i] != head && c(p->nxt[i]->d, x)) p = p->nxt[i];
      bck[i] = p;
    }
    return c(x, p->nxt[0]->d) ? end() : p->nxt[0];
  }

  int new_level() { int l = 0; while (++l < ML && !(pseudo() & pm)); return l; }
  
  iterator insert(const T &x) {
    list_node *p = new list_node(new_level(), x);
    // if we want equal elements to be in the order they were inserted
    // we can replace "find(x)" with "if (find(x) != end()) bck[0] = bck[0]->nxt[0]"
    find(x);
    for (int i = level; i < p->lvl; ++i) { bck[i] = head; }
    for (int i = 0; i < p->lvl; ++i) {
      p->lnk(bck[i]->nxt[i], i);
      bck[i]->lnk(p, i);
    }
    if (p->lvl > level) level = p->lvl;
    return p;
  }

  iterator erase(iterator x) {
    for (int i = 0; i < x.p->lvl; ++i) x.p->prv[i]->lnk(x.p->nxt[i], i);
    delete x--.p;
    return x;
  }
};

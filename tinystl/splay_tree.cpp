/* KTH ACM Contest Template Library
 *
 * tinystl/balanced trees/splay tree
 *
 * Credit:
 *   Based on paper by Tarjan
 *   By Mattias de Zalenski
 */
#include "comparisons.cpp"

template <class T, class C=less<T> >
struct splay_tree {
  typedef T value_type;
  struct node {
    typedef node *P;
    T x; P l, r, p;
    node(T _x, P _l=0, P _r=0) : x(_x), l(_l), r(_r), p(0) { }
    P &c(bool left) { return left ? l : r; } // child pointer reference
  };
  typedef node *P;
  template <bool reverse> struct iter {
    typedef T value_type;
    typedef const splay_tree &TR;
    P p; TR t; iter(P _p, TR _t=0) : p(_p), t(_t) { }

    static P side(P i, bool left = true) { // min or max
      if (i) while (i->c(left)) i = i->c(left);
      return i;
    }
    void succ(bool succ = true) { // pred if succ is false
      if (!p) p = side(t.root, reverse);
      else if (p->c(!succ)) p = side(p->c(!succ), succ); // side of subtree
      else { P i; do i = p, p = i->p; while (p && p->c(!succ) == i); }
    } // ..or first left/right ancestor (or 0)
    iter &operator ++() { succ(!reverse); return *this; }
    iter &operator --() { succ(reverse); return *this; }
    iter operator++(int) { iter s(p, t); succ(!reverse); return s; }
    iter operator--(int) { iter s(p, t); succ(reverse); return s; }
    bool operator==(const iter &s) const { return p==s.p; }
    bool operator!=(const iter &s) const { return p!=s.p; }
    T &operator *() { return p->x; }
    T *operator ->() { return &(p->x); }
    const T &operator *() const { return p->x; }
    const T *operator ->() const { return &(p->x); }
    static iter begin(TR t) { return iter(side(t.root, !reverse), t); }
    static iter end(TR t) { return iter(0, t); }
  };
  typedef iter<false> iterator;
  typedef iter<true> reverse_iterator;

  P root; C c; unsigned n;
  splay_tree(C _c = C()) : root(0), c(_c), n(0) { }
  splay_tree(const splay_tree &s) : root(0), c(s.c), n(0) { copy(s); }
  splay_tree &operator =(const splay_tree &s) { copy(s); return *this; }
  void copy(const splay_tree &_s) {
    clear(); splay_tree &s = (splay_tree &) _s;
    c = s.c;
    for(iterator i = s.begin(); i != s.end(); ++i) insert(*i, true);
  }
  virtual ~splay_tree() { clear(); }

  static void rot(P i, bool left) {
    P j = i->c(!left), p = i->p;
    if (p) p->c(i == p->l) = j;
    j->p = i->p, i->p = j;
    if (left) i->r = j->l, j->l = i;
    else /**/ i->l = j->r, j->r = i;
    j = i->c(!left); if (j) j->p = i;
  }
  static P splay(P i) {
    if (i)
      while (i->p) {
	P p = i->p, g = p->p;
	bool left = i == p->l;
	if (g && p == g->c(left)) rot(g, !left);
	rot(p, !left);
      }
    return i;
  }

  // accessors
  iterator begin() { return iterator::begin(*this); }
  iterator end() { return iterator::end(*this); }
  reverse_iterator rbegin() { return reverse_iterator::begin(*this); }
  reverse_iterator rend() { return reverse_iterator::end(*this); }
  void clear() { while (root) erase(iterator(root, *this)); }
  bool empty() const { return root == 0; }
  unsigned size() { return n; }
  // insert/erase
  iterator insert(const T &x, bool multi) {
    if (root) {
      if (find(x, false) != end() && !multi) return end();
      P l, r; // split:
      if (c(x, root->x)) r = root, l = r->l, r->l = 0;
      else /**//**//**//**/ l = root, r = l->r, l->r = 0;
      root = new node(x, l, r), ++n;
      if (l) l->p = root;
      if (r) r->p = root;
    }
    else
      root = new node(x), ++n;
    return iterator(root, *this);
  }
  void erase(iterator it) {
    P i = it.p; splay(i);
    P l = i->l, r = i->r; // join:
    if (l) while (l->r) rot(l, true), l = l->p;
    if (l) l->r = r, l->p = 0; if (r) r->p = l;
    root = l ? l : r;
    delete i, --n;
  }
  // associative operations
  iterator find(const T &x, bool left = true) {
    P p = root, i = root;
    while (i) {
      p = i;
      if (c(x, i->x)) i = i->l;
      else if (c(i->x, x)) i = i->r;
      else if (i->c(left) &&
	       (left?!c(i->c(left)->x, x):!c(x, i->c(left)->x))) // sic
	i = i->c(left);
      else break;
    }
    root = splay(p);
    return iterator(i, *this);
  }
  iterator lower_bound(const T &x) {
    find(x, true); iterator i(root, *this);
    return c(*i, x) ? ++i : i;
  }
  iterator upper_bound(const T &x) {
    find(x, false); iterator i(root, *this);
    return c(x, *i) ? i : ++i;
  }
};

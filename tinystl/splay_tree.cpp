/* KTH ACM Contest Template Library
 *
 * tinystl/balanced trees/splay tree
 *
 * Credit:
 *   Based on paper by Tarjan
 *   By Mattias de Zalenski
 */

// for less<>:
#include "function.cpp"

template <class T>
struct splay_node {
  typedef splay_node<T> *P;
  T x; P l, r, p;
  splay_node(T _x, P _l=0, P _r=0) : x(_x), l(_l), r(_r), p(0) { }
  P &c(bool left) { return left ? l : r; } // child pointer reference
};

template <class T, bool reverse>
struct splay_node_iterator {
  typedef T value_type;
  typedef splay_node<T> *P;
  typedef splay_node_iterator<T, reverse> sT;
  P p; splay_node_iterator(P _p) : p(_p) { }

  static P side(P i, bool left = true) {
    if (i) while (i->c(left)) i = i->c(left);
    return i;
  }
  static P succ(P i, bool succ = true) { // pred if succ is false
    if (i->c(!succ)) return side(i->c(!succ), succ); // min or max of subtree
    P p = i->p; // or first left/right ancestor (or 0)
    while (p && p->c(!succ) == i) i = p, p = i->p;
    return p;
  }
  static sT begin(P i) { return sT(side(i, !reverse)); }
  static sT end() { return sT(0); }

  sT &operator ++() { p = succ(p, !reverse); return *this; }
  sT &operator --() { p = succ(p, reverse); return *this; }
  sT operator++(int) { sT t(p); p = succ(p, !reverse); return t; }
  sT operator--(int) { sT t(p); p = succ(p, reverse); return t; }
  bool operator==(const sT &s) const { return p==s.p; }
  bool operator!=(const sT &s) const { return p!=s.p; }
  T &operator *() { return p->x; }
  const T &operator *() const { return p->x; }
  const T *operator ->() const { return &(p->x); }
};

template <class T, class C=less<T> >
struct splay_tree {
  typedef splay_node<T> *P;

  typedef T value_type;
  typedef P iterator;

  P root; C comp; unsigned n;
  splay_tree(C _comp = C()) : root(0), comp(_comp), n(0) { }
  ~splay_tree() { while (root) erase(root); }

  static void rot(P i, bool left) {
    P j = i->c(!left), p = i->p;
    if (p) p->c(i == p->l) = j;
    j->p = i->p; i->p = j;
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

  bool empty() const { return root == 0; }
  iterator find(const T &x, bool left = false) {
    P p = root, i = root;
    while (i) {
      p = i;
      if (comp(x, i->x)) i = i->l;
      else if (comp(i->x, x)) i = i->r;
      else if (i->c(left) && !comp(x, i->c(left)->x)) i = i->c(left); //
      else break;
    }
    root = splay(p);
    return i;
  }
  void insert(const T &x) {
    if (root) {
      find(x);
      P l, r; // split:
      if (comp(x, root->x)) r = root, l = r->l, r->l = 0;
      else /* */ /**/ /* */ l = root, r = l->r, l->r = 0;
      root = new splay_node<T>(x, l, r), ++n;
      if (l) l->p = root;
      if (r) r->p = root;
    }
    else
      root = new splay_node<T>(x), ++n;
  }
  void erase(iterator i) {
    splay(i);
    P l = i->l, r = i->r; // join:
    if (l) while (l->r) rot(l, true), l = l->p;
    if (l) l->r = r, l->p = 0; if (r) r->p = l;
    root = l ? l : r;
    delete i, --n;
  }
};

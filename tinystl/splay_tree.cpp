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

template <class T, class C=less<T> >
struct splay_tree {
  typedef splay_node<T> *P;

  typedef T value_type;

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

  void clear() { while(root) erase(root); }
  bool empty() const { return root == 0; }
  P find(const T &x, bool left = false) {
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
  void erase(P i) {
    splay(i);
    P l = i->l, r = i->r; // join:
    if (l) while (l->r) rot(l, true), l = l->p;
    if (l) l->r = r, l->p = 0; if (r) r->p = l;
    root = l ? l : r;
    delete i, --n;
  }
};

template <class T, class C, bool reverse>
struct splay_node_iterator {
  typedef T value_type;
  typedef splay_node<T> *P;
  typedef splay_node_iterator<T, C, reverse> sT;
  typedef const splay_tree<T, C> &TR;
  P p; TR t; splay_node_iterator(P _p, TR _t=0) : p(_p), t(_t) { }

  static P side(P i, bool left = true) {
    if (i) while (i->c(left)) i = i->c(left);
    return i;
  }
  void succ(bool succ = true) { // pred if succ is false
    if (!p) p = side(t.root, reverse);
    else if (p->c(!succ)) p = side(p->c(!succ), succ); // min or max of subtree
    else { P i; do i = p, p = i->p; while (p && p->c(!succ) == i); }
  } // ..or first left/right ancestor (or 0)
  static sT begin(TR t) { return sT(side(t.root, !reverse), t); }
  static sT end(TR t) { return sT(0, t); }

  sT &operator ++() { succ(!reverse); return *this; }
  sT &operator --() { succ(reverse); return *this; }
  sT operator++(int) { sT s(p, t); succ(!reverse); return s; }
  sT operator--(int) { sT s(p, t); succ(reverse); return s; }
  bool operator==(const sT &s) const { return p==s.p; }
  bool operator!=(const sT &s) const { return p!=s.p; }
  T &operator *() { return p->x; }
  const T &operator *() const { return p->x; }
  const T *operator ->() const { return &(p->x); }
};

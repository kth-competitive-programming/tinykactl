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

  typedef P iterator;
  static iterator min(iterator i) { if (i) while (i->l) i = i->l; return i; }
  static iterator max(iterator i) { if (i) while (i->r) i = i->r; return i; }
  static iterator succ(iterator i, bool succ = true) {
    if (i->c(!succ)) return succ ? min(i->r) : max(i->l);
    iterator p = i->p;
    while (p && p->c(!succ) == i) i = p, p = i->p;
    return p;
  }
};

template <class T, class C=less<T> >
struct splay_tree {
  typedef splay_node<T> *P;

  typedef T value_type;
  typedef P iterator;

  P root; C comp; splay_tree(C _comp = C()) : root(0), comp(_comp) { }

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

  bool empty() { return root == 0; }
  iterator find(const T &x) {
    P p = root, i = root;
    while (i) {
      p = i;
      if (comp(x, i->x)) i = i->l;
      else if (comp(i->x, x)) i = i->r;
      //else if (i->l && !comp(x, i->l->x)) i = i->l; // duplicate keys
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
      else /**//**/ l = root, r = l->r, l->r = 0;
      root = new splay_node<T>(x, l, r);
      if (l) l->p = root;
      if (r) r->p = root;
    }
    else
      root = new splay_node<T>(x);
  }
  void erase(iterator i) {
    splay(i);
    P l = i->l, r = i->r; // join:
    if (l) while (l->r) rot(l, true), l = l->p;
    if (l) l->r = r, l->p = 0; if (r) r->p = l;
    root = l ? l : r;
    delete i;
  }
};

template <class T>
struct splay_node_iterator {
  typedef T value_type;
  typedef splay_node<T> *P;
  typedef splay_node_iterator<T> sT;
  typedef splay_node<T> N;
  P p; splay_node_iterator(P _p) : p(_p) { }

  sT &operator ++() { p = N::succ(p, true); return *this; }
  sT &operator --() { p = N::succ(p, false); return *this; }
  sT operator++(int) { sT t(p); p = N::succ(p, true); return t; }
  sT operator--(int) { sT t(p); p = N::succ(p, false); return t; }
  bool operator==(const sT &s) const { return p==s.p; }
  T &operator *() { return p->x; }
  const T &operator *() const { return p->x; }
  T *operator ->() const { return &(operator *()); }
};

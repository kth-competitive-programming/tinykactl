/* KTH ACM Contest Template Library
 *
 * tinystl/balanced trees/splay tree
 *
 * Credit:
 *   Based on paper by Tarjan
 *   By Mattias de Zalenski
 */

template <class T>
struct splay_node {
  typedef splay_node<T> *P;
  T x; P l, r, p;
  splay_node(T _x, P _l=0, P _r=0) : x(_x), l(_l), r(_r), p(0) { }
  P &c(bool left) { return left ? l : r; } // child pointer reference
};

template <class T>
struct splay_tree {
  typedef splay_node<T> *P;
  typedef T value_type;
  typedef P iterator;
  P root; splay_tree() : root(0) { }
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
  static void split(P i, P &l, P &r) {
    l = splay(i);
    r = l->r; l->r = 0;
    if (r) r->p = 0;
  }
  static void join(P l, P r, P &i) {
    if (l) while (l->r) rot(l, true), l = l->p;
    if (l) l->r = r; if (r) r->p = l;
    i = l ? l : r;
  }
  bool empty() { return root == 0; }
  iterator find(const T &x) {
    P p = root, i = root;
    while (i) {
      p = i;
      if (x < i->x) i = i->l;
      else if (x > i->x) i = i->r;
      //else if (i->l && x >= i->l->x) i = i->l; // for duplicate keys
      else break;
    }
    root = splay(p);
    return i;
  }
  void insert(const T &x) {
    if (root) {
      //while (i) p = i, i = p->c(x < p->x);
      find(x);
      P l, r; split(root, l, r);
      root = new splay_node<T>(x, l, r);
      if (l) l->p = root;
      if (r) r->p = root;
    }
    else
      root = new splay_node<T>(x);
  }
  void erase(iterator i) {
    splay(i);
    join(i->l, i->r, root);
    if (root) root->p = 0;
    delete i;
  }
};

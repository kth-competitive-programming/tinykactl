#include "utility.cpp"

template <class T>
struct splay_node {
  typedef splay_node<T> sT;
  T x; sT *left, *right, *parent;
  splay_node(T _x, sT *l = 0, sT *r = 0, sT *p = 0)
    : x(_x), left(l), right(r), parent(p) {
    if (l) l->parent = this;
    if (r) r->parent = this;
  }
};

template <class T>
struct splay_tree {
  typedef T value_type;
  typedef splay_node<T> sT;
  typedef sT *iterator;
  sT *root; splay_tree() : root(0) { }
  static void rot(iterator i, bool left) {
    iterator p = i->parent;
    iterator j = left ? i->right : i->left;
    iterator k = left ? j->left : j->right;
    if (p) if (p->left == i) p->left = j; else p->right = j;
    j->parent = p;
    i->parent = j;
    if (left) i->right = k; else i->left = k;
    if (left) j->left = i; else j->right = i;
    if (k) k->parent = i;
  }
  static iterator splay(iterator i) {
    if (i) {
      iterator pp;
      for (iterator p = i->parent; p; i = p, p = pp) {
	pp = p->parent;
	if (i == p->left) {
	  //if (pp && p == pp->left) rot(pp, false);
	  rot(p, false); p = i;
	}
	else {
	  //if (pp && p == pp->right) rot(pp, true);
	  rot(p, true); p = i;
	}
      }
    }
    return i;
  }
  typedef pair<iterator, iterator> Pii;
  static Pii split(iterator i) {
    i = splay(i);
    iterator j = i->right;
    i->right = 0;
    if (j) j->parent = 0;
    return Pii(i, j);
  }
  static iterator join(iterator i, iterator j) {
    while (i->right) rot(i, false);
    i->right = j;
    if (j) j->parent = i;
    return i;
  }
  bool empty() { return root == 0; }
  iterator find(const T &x) {
    iterator p = root, i = root;
    while (i) {
      p = i;
      if (x < i->x) i = i->left;
      else if (x > i->x) i = i->right;
      else break;
    }
    root = splay(p);
    return i;
  }
  void insert(const T &x) {
    if (root) {
      find(x);
      Pii pii = split(root);
      root = new sT(x, pii.first, pii.second);
    }
    else
      root = new sT(x);
  }
  void erase(const T &x) {
    find(x);
    iterator i = root;
    root = join(i->left, i->right);
    if (root) root->parent = 0;
    delete i;
  }
};

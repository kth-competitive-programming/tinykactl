/* KTH ACM Contest Template Library
 *
 * tinystl/stack (linked list implementation)
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 */

template <class T>
struct stack_entry {
  typedef stack_entry<T> sT;
  T x; sT *next;
  stack_entry(const T &_x, sT *_next = 0) : x(_x), next(_next) { }
};

template <class T>
struct stack {
  typedef T value_type;
  typedef stack_entry<T> sT;
  sT *root; stack() : root(0) { }
  ~stack() { while( !empty() ) pop(); }
  bool empty() { return root == 0; }
  void push(const T &x) { root = new sT(x, root); }
  void pop() { sT *o=root; root = root->next; delete o; }
  T &top() { return root->x; }
  const T &top() const { return root->x; }
};

template <class T>
struct stack_entry {
  typedef stack_entry<T> sT;
  T x; sT *next;
  stack_entry(T _x, sT *_next = 0) : x(_x), next(_next) { }
};

template <class T>
struct stack {
  typedef T value_type;
  typedef stack_entry<T> sT;
  sT *root; stack() : root(0) { }
  bool empty() { return root == 0; }
  void push(T x) { root = new sT(x, root); }
  void pop() { root = root.next; }
  T &top() { return root.x; }
  const T &top() const { return root.x; }
};

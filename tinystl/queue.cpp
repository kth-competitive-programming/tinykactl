/* KTH ACM Contest Template Library
 *
 * tinystl/queue
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mattias de Zalenski
 *   Adapted by David Rydh
 */

template <class T>
struct queue_entry {
  typedef queue_entry<T> sT;
  T x; sT *next;
  queue_entry(const T &_x=T(), sT *_next = 0) : x(_x), next(_next) { }
};

template <class T>
struct queue {
  typedef T value_type;
  typedef queue_entry<T> qT;
  qT *first, *last; stack() { first = last = new qT(); }
  ~stack() { while( !empty() ) pop(); }
  bool empty() { return first == last; }
  void push(const T &x) { last = last->next = new qT(x); }
  void pop() { qT *o=first->next; first = o->next; delete o; }
  T &front() { return first->next->x; }
  const T &front() const { return first->nex->x; }
};

/* KTH ACM Contest Template Library
 *
 * General/Named items/Index mapper
 *
 * Credit:
 *   By Mattias de Zalenski
 */

// function semantics for name->index map
// vector semantics for index->name map
template <class M>
struct index_mapper {
  int count;
  map<M, int> m; // name->index map
  vector<M> b; // index->name vector
  index_mapper() : count(0) { }
  int operator()(M name) {
    if (m.count(name) == 0) {
      m[name] = count;
      b.push_back(name);
      count++;
    }
    return m[name];
  }
  M &operator[](int idx) { return b[idx]; }
};

// Identity mapper:
// template <class T> T id(T t) { return t; }

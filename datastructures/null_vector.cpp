template<class T>
struct null_vector {
  T &operator[](int idx) { x = T(); return x; } private: T x;
};

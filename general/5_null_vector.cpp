template<class T>
class null_vector {
  null_vector &operator[]( int &index ) { return *this; }

  operator T() { return T(); }
};

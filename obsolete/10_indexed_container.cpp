/*****************************************************************************
 * 
 * General1: indexed_container
 * ===========================
 *
 * Get the index/value of an iterator (in a map or a vector)
 *
 /****************************************************************************/

template<class T>
struct indexed_container {
public:
  typedef typename T::value_type    value_type;
  typedef int                       index_type;

  template<class I>
  static int indexof( const T &container, I iter ) {
    return iter-container.begin();
  }

  template<class I>
  static typename T::value_type &valueof( T &container, I iter ) {
    return *iter;
  }

  template<class I>
  static const typename T::value_type &valueof( const T &container, I iter ) {
    return *iter;
  }
};

template< class K, class T, class C, class A>
struct indexed_container< map<K,T,C,A> > {
  typedef T  value_type;
  typedef K  index_type;

  template<class I>
  static K indexof( const map<K,T,C,A> &map, I iter ) {
    return (*iter).first;
  }

  template<class I>
  static T &valueof( map<K,T,C,A> &map, I iter ) {
    return (*iter).second;
  }

  template<class I>
  static const T &valueof( const map<K,T,C,A> &map, I iter ) {
    return (*iter).second;
  }
};

/* KTH ACM Contest Template Library
 *
 * <area>/<problem>/<algorithm>
 *
 * Credit:
 *   Variation of std::priority_queue
 *   By David Rydh
 *
 *
 * The class of heap elements, T, must support the method set_position.
 *
 * bool                          empty();
 * Container::size_type          size();
 * [const] Container::value_type top() [const];
 * void                          push( const Container::value_type &x );
 * void                          pop();
 * void                          key_increased( Index p );
 * void                          key_decreased( Index p );
 */

#include <vector>

template<class T, class Container=vector<T>, class Compare=less<T> >
class upd_heap {
  Container  v;
  typedef Container::difference_type Index;

public:
  upd_heap();

  bool                        empty() { return v.empty(); }
  Container::size_type        size() { return v.size(); }
  Container::value_type       top() { return v.front(); }
  const Container::value_type top() const { return v.front(); }

  void push( const Container::value_type &x ) {
    v.push_back( x );
    x.set_position( size()-1 );
    key_decreased( size()-1 );
  }

  void pop() {
    v[0].set_position( -1 );
    (v[0] = v[size()-1]).set_position( 0 );

    v.pop_back();
    key_increased( 0 );
  }

  void key_increased( Index p ) {
    Index parent = (p-1)/2;

    if( p>=0 && v[p] > v[parent] ) {
      swap( p, parent );
      key_increased( parent );
    }
  }

  void key_decreased( Index p ) {
    Index left = p*2+1, right = p*2+2, exc = p;
    T     &value = v[p];

    if( left < size() && v[left] < value ) {
      exc = left;
      value = v[left];
    }
    if( right < size() && v[right] < value )
      exc = right;

    if( exc != p ) {
      swap( p, exc );
      key_decreased( exc );
    }
  }

private:
  void swap( Index p1, Index p2 ) {
    v[p1].set_position( p2 );
    v[p2].set_position( p1 );

    swap( v[p1], v[p2] );
  }
};

/*****************************************************************************
 * 
 * General1: class indexed_comparator, indexed, function isort
 * ===========================================================
 *
 * ------------------------------------------------------------------------- *
 *
 * NADA acmlib (10 March 2002)
 * Templates for KTH-NADA, Ballons'R'Us, ACM 2001-2002
 *   Swedish competition, Link?ping 6 Oct 2001
 *   Revised for SWERC, Portu, Portugal 17 Nov 2001
 *   Revised for World Finals, Honolulu, 23 Mar 2002
 *   David Rydh, Mattias de Zalenski, Fredrik Niemel?
 *
 *****************************************************************************/

template<class V >
struct indexed_less {
  const V &v; // array
  indexed_less( const V &v_ ) : v(_v) { }
  bool operator()( int a, int b ) const { return v[a] < v[b]; }
};

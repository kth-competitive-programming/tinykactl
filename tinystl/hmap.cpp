/* KTH ACM Contest Template Library
 *
 * tinystl/hash map
 *
 * Credit:
 *   Alexander Stepanov
 *   Based on STL
 *   By Mikael Goldmann
 *   Hash functions added and lines deleted by Per Austrin
 */

#include <stdlib.h>         // needs size_t
#include "comparisons.cpp"  // needs equal_to

// Pseudo-generic hash class using Adler-32 by Mark Adler.
// sizeof(x) needs to be something useful in order for this to work.
template <class R>
struct Hash {
  static const int crcbase = 65521;
  size_t operator()(const R &x) const {
    char* s = (char*)&x; int s1 = 1, s2 = 0;
    for (size_t i = 0; i < sizeof(x); ++i)
      (s1 += s[i]) %= crcbase, (s2 += s1) %= crcbase;
    return (s2 << 16 | s1);
  }
};

// Special version of the Hash class above for strings
struct Hash<char*> {
  static const int crcbase = 65521;
  size_t operator()(const char *x) const {
    int s1 = 1, s2 = 0;
    for (; *x; ++x) (s1 += *x) %= crcbase, (s2 += s1) %= crcbase;
    return (s2 << 16 | s1);
  }
};

template <class K, class T, class H = Hash<K>, class EQ = equal_to<K> >
struct hmap {
  typedef K Tk;
  typedef T Tv;

  struct Entry { 
    Tk key;  Tv val;  Entry *next;
    Entry(Tk k=Tk(), Tv v=Tv(), Entry* n=0) : key(k), val(v), next(n) {};
  };
  typedef Entry* Pent;
  

  H hash;
  EQ eql;
  size_t nit;
  size_t cap;
  Tv def_val;
  Pent *vec;
  const float max_load;

  hmap(size_t c=10000, Tv dv=T(), float ml=0.6)
    : nit(0), cap(c), def_val(dv), vec(new Pent[cap]), max_load(ml) {}
  virtual ~hmap() { clear(); delete[] vec; }

  void clear() {for (Pent* i=vec+cap-1; i >= vec; --i) del(*i); }
  size_t size() const { return nit; }
  bool member(const Tk & k) const { return find(k); }
  void remove(const Tk &k) { size_t i = hash(k)%cap; vec[i] = rm(k, vec[i]); }

  Tv & operator[](const Tk & k) {
    Entry *e = find(k);
    if (!e) e = add(k, def_val);
    return e->val;
  }

// protected:
  Pent find(const Tk &k) const {
    for (Pent e = vec[hash(k) % cap]; e; e = e->next)
      if (eql(e->key, k)) return e;
    return 0;
  }
  
  void grow() { 
    Pent *ov = vec;
    size_t oc = cap;
    vec = new Pent[cap = 2*cap + 7]; 
    while (oc--)
      for (Pent e = ov[oc]; e; e = e->next) {
	int j = hash(e->key) % cap;
	e->next = vec[j];
	vec[j] = e;
      }	
    delete[] ov;
  }

  Pent rm(const Tk & k, Pent p) { 
    if (!p) return 0; 
    Pent q = p->next;
    if (eql(p->key, k)) { delete p; --nit; return q; }
    else                { p->next = rm(k, q); return p; }
  }

  Pent add(const Tk &k, const Tv &v) {
    if (cap * max_load < nit) grow();
    size_t i = hash(k) % cap; 
    ++nit;
    return (vec[i] = new Entry(k, v, vec[i]));
  }

  void del(Pent &e) { if (e) { del(e->next); delete e; e = 0;}}
};

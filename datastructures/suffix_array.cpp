/* KTH ACM Contest Template Library
 *
 * Data Structures/Suffix Array
 *
 * Credit:
 *   By Per Austrin
 */

#include <cstring>

struct suffix_array {
  int length, *suffixes, *position, *count;
  char *text, *border;

  suffix_array(int maxlen): 
    length(0), suffixes(new int[maxlen]),
    position(new int[maxlen]), count(new int[maxlen]),
    border(new int[maxlen])  {}

  void set_text(char *_text) {
    text = _text;
    length = strlen(text);
    sort_suffixes();
  }

  void sort_init() {
    int pos[257], i;
    char *p;
    
    memset(pos, 0, sizeof(pos));
    for(p = text; p < text + a->length; ++p) ++pos[*p+1];
    
    for(int i = 1; i < 256; ++i) {
      if((pos[i] += pos[i-1]) >= a->length) break;
      border[pos[i]] = 1;
    }
    *border = 1;
    
    for(p = text; p < text + length; ++p)
      suffixes[pos[(int) *p]++] = p - text;
    return 1;
  }

  void sort_suffixes() {
   int H, i, N = length;
   memset(border, 0, N);

   for(H = sa_sort_init(); H < length; H *= 2) {
      int left = 0, done = 1;

      for(i = 0; i < N; ++i) {
	 if(border[i]) left = i;
	 position[suffixes[i]] = left;
	 count[i] = 0;
      }

      left = 0;
      for( i = 0; i < N; ++i) {
	 int suff = suffixes[i];
	 if(suff >= H) {
	    position[suff - H] += count[position[suff - H]]++;
	    border[position[suff - H]] |= 2;
	 }
	 if(suff >= N - H) {
	    position[suff] += count[position[suff]]++;
	    border[position[suff]] |= 2;
	 }

	 if(i == N - 1 || (border[i+1] & 1)) {
	    for( ; left <= i; ++left) {
	       suff = suffixes[left] - H;
	       if(suff < 0 || !(border[position[suff]] & 2)) 
		 continue;
	       suff = position[suff];
	       for (++suff; suff < N && (border[suff]^2) == 0; ++suff)
		  border[suff] &= ~2;
	    }
	 }
      }

      for(i = 0; i < N; ++i) {
	 suffixes[position[i]] = i; 
	 done &= (border[i] = !!border[i]);
      }

      if (done) break;
   }
  }
};

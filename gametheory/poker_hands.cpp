/* KTH ACM Contest Template Library
 *
 * Games/Card Games/Poker Hands
 *
 * Poker hands.  Cards are assumed to be integers from 0..51 where 0
 * is the ace of the first color, 12 the king of the first color, 13
 * the ace of the second color, and so on.
 *
 * Credit:
 *   By Per Austrin
 */


#include <string>

string hand_names[] = {
  "highest-card",
  "one-pair",
  "two-pairs",
  "three-of-a-kind",
  "straight",
  "flush",
  "full-house",
  "four-of-a-kind",
  "straight-flush"};

inline int color(int card) { return card / 13; }
inline int value(int card) { return card % 13; }

int hand_value(int hand[5]) {
  int pairs = 0, triples = 0, quads = 0;
  int vcnt[13]; // count of each value
  int ccnt[4];  // count of each color
  bool flush = false, straight = true;
  for (int i = 0; i < 13; ++i) vcnt[i] = 0;
  for (int i = 0; i < 4; ++i)  ccnt[i] = 0;
  for (int i = 0; i < 5; ++i) {
    int v = ++vcnt[value(hand[i])];
    if (v == 2)      ++pairs;
    else if (v == 3) --pairs, ++triples;
    else if (v == 4) --triples, ++quads;
    if (++ccnt[color(hand[i])] == 5)
      flush = true;
  }
  int began = -1;
  bool rstraight = true; // royal straight is special (value(ace) = 0)
  for (int i = 0; i < 13; ++i)
    if (vcnt[i]) {
      if (began == -1)
	began = i;
      straight &= i < began + 5;
      rstraight &= !began && (!i || i >= 9);
    }
  straight |= rstraight;
  straight &= !pairs && !triples && !quads;
  if (straight && flush) {        // straight flush
    return 8;
  } else if (quads) {             // four of a kind
    return 7;
  } else if (triples && pairs) {  // full house
    return 6;
  } else if (flush) {             // flush
    return 5;
  } else if (straight) {          // straight
    return 4;
  } else if (triples) {           // three of a kind
    return 3;
  } else if (pairs > 1) {         // two pairs
    return 2;
  } else if (pairs) {             // one pair
    return 1;
  }
  // no hand
  return 0;
}

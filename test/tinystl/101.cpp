/******************************************
 *
 * @JUDGE_ID: 25719RJ 101 C++
 *
 * Problem 101 "The Blocks Problem"
 *
 * David Rydh, <f99-dry@nada.kth.se>
 * November 2001
 *****************************************/

#include <cstdlib>
#include <iostream>
#include <string>

#include "../../tinystl/vector.cpp"
#include "../../tinystl/list.cpp"

const int N = 25;

vector< list<int> >  world;
list<int>::iterator  blocks[N];
int                  position[N];

void reset( list<int> &l, const list<int>::iterator &start,
	    const list<int>::iterator &end )
{
  list<int>::iterator ptr;
  int                 block;

  for( ptr=start, ++ptr; ptr!=end; ) {
    block = *ptr;
    position[block] = block;
    world[block].splice( world[block].end(), l, ptr++ );
  }
}

void move( list<int> &l, const list<int>::iterator &start,
	    const list<int>::iterator &end, int to_pos )
{
  list<int>::iterator ptr;

  for( ptr=start; ptr!=end; ptr++ )
    position[*ptr] = to_pos;

  world[to_pos].splice( world[to_pos].end(), l, start, end );
}


int main() {
  int                  i, n;
  list<int>::iterator  ptr, end;

  cin >> n;

  world.resize( n );

  for( i=0; i<n; i++ ) {
    world[i].push_back( i );
    blocks[i] = world[i].begin();
    position[i] = i;
  }

  while( true ) {
    string command, prep;
    int    a,b;
    bool   pile_a, pile_b;

    cin >> command;
    if( command == "quit" )
      break;

    cin >> a >> prep >> b;
    if( a == b ) // Illegal?
      continue;

    pile_a = (command == "pile");
    pile_b = (prep == "over");

    // Check for illegal moves
    int                  pos_a, pos_b, block;
    bool                 illegal = false;

    pos_a = position[a];
    pos_b = position[b];

    ptr = blocks[a];
    end = world[pos_a].end();
    while( ++ptr != end ) {
      block = *ptr;
      if( block == b || (!pile_a && (block == pos_a ||
				     (!pile_b && block == pos_b))) )
      {
	illegal = true;
	break;
      }
    }

    ptr = blocks[b];
    end = world[pos_b].end();
    while( ++ptr != end ) {
      block = *ptr;
      if( block == a || (!pile_b && (block == pos_b ||
				     (!pile_a && block == pos_a))) )
      {
	illegal = true;
	break;
      }
    }

    if( !illegal ) {
      if( !pile_a )
	reset( world[pos_a], blocks[a], world[pos_a].end() );
      if( !pile_b )
	reset( world[pos_b], blocks[b], world[pos_b].end() );

      move( world[pos_a], blocks[a], world[pos_a].end(), pos_b );
    }
  }

  for( i=0; i<n; i++ ) {
    cout << i << ":";

    ptr = world[i].begin();
    end = world[i].end();
    while( ptr != end ) {
      cout << " " << *ptr;
      ptr++;
    }
    cout << endl;
  }

  return 0;
}

/* KTH ACM Contest Template Library
 *
 * Input/Graphs/Input methods
 *
 * Credit:
 *   By Mattias de Zalenski
 */
#include <iostream>
#include <vector>

using namespace std;

// Input methods:
//  adjacency matrix
//  all vertex edge list
//  named edge list
//  weighted edge list
//  weighted named edge list
//  separate edges
//  separate weighted edges
//  separate named edges
//  separate weighted named edges

// Take an extra type I to allow int[][] with char input, for example
template <class M, class I>
void matrix_input(istream &in, M &g, I x) {
  int v;
  in >> v; // number of vertices
  for (int i = 0; i < v; i++)
    for (int j = 0; j < v; j++) {
      in >> x;
      g[i][j] = x;
    }
}

void edge_list_input(istream &in, vector< vector< int > > &g,
		     bool undirected = true) {
  int v;
  in >> v; // number of vertices
  g.resize(v);
  for (int i = 0; i < v; i++) {
    int l;
    in >> l; // edge list length
    for (int j = 0; j < l; j++) {
      int k;
      in >> k;
      g[i].push_back(k);
      if (undirected)
	g[k].push_back(i);
    }
  }
}

template <class W>
void wedge_list_input(istream &in, vector< vector< pair< int, W > > > &g,
		      bool undirected = true) {
  int v;
  in >> v; // number of vertices
  for (int i = 0; i < v; i++) {
    int l;
    in >> l; // edge list length
    for (int j = 0; j < l; j++) {
      int k;
      W w;
      in >> k >> w;
      g[i].push_back(make_pair(k, w));
      if (undirected)
	g[k].push_back(make_pair(i, w));
    }
  }
}

template <class M, class N>
void nedge_list_input(istream &in, M mapper, N name,
		      vector< vector< int > > &g,
		      bool undirected = true) {
  int n;
  in >> n;
  for (int i = 0; i < n; i++) {
    in >> name;
    int m = mapper(name);
    if (m >= g.size()) g.resize(m + 1);
    int l;
    in >> l; // edge list length
    for (int j = 0; j < l; j++) {
      in >> name;
      int k = mapper(name);
      if (k >= g.size()) g.resize(k + 1);
      g[m].push_back(k);
      if (undirected)
	g[k].push_back(m);
    }
  }
}

template <class M, class N, class W>
void nwedge_list_input(istream &in, M mapper, N name,
		       vector< vector< int, W > > &g,
		       bool undirected = true) {
  int n;
  in >> n;
  for (int i = 0; i < n; i++) {
    in >> name;
    int m = mapper(name);
    if (m >= g.size()) g.resize(m + 1);
    int l;
    in >> l; // edge list length
    for (int j = 0; j < l; j++) {
      in >> name;
      int k = mapper(name);
      if (k >= g.size()) g.resize(k + 1);
      W w;
      in >> w;
      g[m].push_back(make_pair(k, w));
      if (undirected)
	g[k].push_back(make_pair(m, w));
    }
  }
}

void edges_input(istream &in, vector< vector< int > > &g,
		 bool undirected = true) {
  int v;
  in >> v; // number of vertices
  g.resize(v);
  int e;
  in >> e; // number of edges
  for (int i = 0; i < e; i++) {
    int a, b;
    in >> a >> b;
    g[a].push_back(b);
    if (undirected)
      g[b].push_back(a);
  }
}

template <class W>
void wedges_input(istream &in, vector< vector< pair<int, W> > > &g,
		  bool undirected = true) {
  int v;
  in >> v; // number of vertices
  g.resize(v);
  int e;
  in >> e; // number of edges
  for (int i = 0; i < e; i++) {
    int a, b;
    W w;
    in >> a >> b >> w;
    g[a].push_back(make_pair(b, w));
    if (undirected)
      g[b].push_back(make_pair(a, w));
  }
}

template <class M, class N>
void nedges_input(istream &in, M mapper, N name,
		  vector< vector< int > > &g,
		  bool undirected = true) {
  int e;
  in >> e; // number of edges
  for (int i = 0; i < e; i++) {
    int a, b;
    in >> name;
    a = mapper(name);
    if (g.size() <= a) g.resize(a + 1);
    in >> name;
    b = mapper(name);
    if (g.size() <= b) g.resize(b + 1);
    g[a].push_back(b);
    if (undirected)
      g[b].push_back(a);
  }
}

template <class M, class N, class W>
void nwedges_input(istream &in, M mapper, N name,
		   vector< vector< pair<int, W> > > &g,
		   bool undirected = true) {
  int e;
  in >> e; // number of edges
  for (int i = 0; i < e; i++) {
    int a, b;
    in >> name;
    a = mapper(name);
    if (g.size() <= a) g.resize(a + 1);
    in >> name;
    b = mapper(name);
    if (g.size() <= b) g.resize(b + 1);
    W w;
    in >> w;
    g[a].push_back(make_pair(b, w));
    if (undirected)
      g[b].push_back(make_pair(a, w));
  }
}

// conversion

template <class R>
void adj2edge(R &g, int v, vector< vector< int > > &h) {
  for (int i = 0; i < v; i++)
    for (int j = 0; j < v; j++)
      if (g[i][j])
	h[i].push_back(j);
}

template <class R, class W>
void adj2wedge(R &g, int v, vector< vector< pair<int, W> > &h) {
  for (int i = 0; i < v; i++)
    for (int j = 0; j < v; j++)
      if (g[i][j])
	h[i].push_back(make_pair(j, g[i][j]));
}

template <class R>
void edge2adj(vector< vector< int > > &g, R &h) {
  for (int i = 0; i < (int) g.size(); i++)
    for (int j = 0; j < (int) g[i].size(); j++)
      h[i][g[i][j]] = true;
}

template <class W, class R>
void wedge2adj(vector< vector< pair<int, W> > > &g, R &h) {
  for (int i = 0; i < (int) g.size(); i++)
    for (int j = 0; j < (int) g[i].size(); j++)
      h[i][g[i][j].first] = g[i][j].second;
}

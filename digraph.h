#ifndef __DIGRAPH_H
#define __DIGRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

class DigraphMatrix
{
private:
	//# of vertices
	int n;
	//# of edges
	int m;
	//traversing the matrix. u is the outer vector (starting point) v is the inner vector, endpoint
	unsigned int u, v;
	//adjacency matrix
	vector<vector<bool>> matrix;
	unordered_map<int, mark_t> vertex;
	vector<int> explore;
public:

  DigraphMatrix(const string& filename);

  void DFSRecursive(int, vector<int>&);  
  void DFS(vector<int>& stack);
  vector<int> topologicalSort();
  int findMin();

};

#endif
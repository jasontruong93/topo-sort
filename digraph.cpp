#include "digraph.h"
/*
* Members: Nghia Truong, Muhammed Ademola
* Project 3: Topological Sort
*/

/*
* Navigator: Muhammed Ademola
* Driver: Nghia Truong
* function to read the file and store graph in adjacency matrix*/
DigraphMatrix::DigraphMatrix(const string& filename) {
	u = 0;
	v = 0;
	m = 0;
	n = 0;
	//open and read the file
	ifstream iFile(filename);
	
	int line_number = 0;

	while (!iFile.eof()) {
		string line;
		getline(iFile, line);

		stringstream ss(line);
		/*
		 u and v, will be in the range 0 to n − 1, 
		 and they represent the endpoints of an edge in the graph. Specifically, they
		 represent an edge from u to v.
		*/
		unsigned int u = 0, v = 0;

		//first line is the number of vertices and edges
		if (line_number == 0) {
			ss >> n >> m;
			matrix.resize(n);

			//initialize the matrix and mark all undiscovered
			for (int i = 0; i < n; i++){
				vertex.insert(make_pair(i, UNDISCOVERED));
				matrix[i].resize(n);
				for (int j = 0; j < n; j++) 
					matrix[i][j] = false;	
			}	
		}
		else{//mark all adjacencies
			if (line != "\0") {
				ss >> u >> v;
				matrix[u][v] = true;

				//cout << u << " " << v << endl;
			}
			
		}
		line_number++;
	}
}

/*
* Navigator: Nghia Truong
* Driver: Muhammed Ademola
* function to make sure everything is DISCOVERED*/
void DigraphMatrix::DFS(vector<int>& explore) {
	DFSRecursive(findMin(), explore);
	for (int i = 0; i < n; i++)
		if (vertex[i] == UNDISCOVERED)
			DFSRecursive(i, explore);
}

/*
* Navigator: Nghia Truong
* Driver: Muhammed Ademola
* This function represents the DFS where explored vertices will be added to the vector*/
void DigraphMatrix::DFSRecursive(int row, vector<int>& explore) {
	vertex[row] = DISCOVERED;

	//iterate the matrix
	for (int i = 0; i < n; ++i) {
		if (matrix[row][i] && vertex[i] == UNDISCOVERED) {
			DFSRecursive(i, explore);
		}
		//find the cycle, if matrix = true and vertex also discovered ->throw exception
		else if (matrix[row][i] && vertex[i] == DISCOVERED) {		
			throw exception();
		}
	}	

	vertex[row] = EXPLORED;
	explore.push_back(row);
}

/*
* Navigator: Nghia Truong
* Driver: Muhammed Ademola
* function to start topological Sort*/
vector<int> DigraphMatrix::topologicalSort(){
	//stack contain explored vertices
	DFS(this->explore);
	
	return this->explore;
}

/*
* Navigator: Muhammed Ademola
* Driver: Nghia Truong
* Function to find the minimum vertex*/
int DigraphMatrix::findMin() {
	for (int j = 0; j < n; j++) {
		if (vertex.find(j) != vertex.end())
			return j;
	}
	return -1;
}

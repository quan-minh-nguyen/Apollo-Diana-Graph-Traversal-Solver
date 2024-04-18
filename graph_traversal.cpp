//Name: Quan Minh Nguyen

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include <list>
#include <queue>
#include <algorithm>
#include <cstdlib>

using namespace std;

class Graph {
    int vertices;
    list<int> *adj;
public:
    Graph(int vertices){
    	this->vertices = vertices;
    	adj = new list<int>[vertices];
    }
    
    void addEdge(int vertex1, int vertex2){
    	adj[vertex1].push_back(vertex2);
    }
    
    vector<int> findPath(int current, int end);
};


vector<int> Graph::findPath(int current, int end) {
    if (current == end) {
        return {};
    }

    bool *visited = new bool[vertices];
    vector<int> parent(vertices, -1);

    for (int i = 0; i < vertices; i++){
        visited[i] = false;
    }

    list<int> queue;
    visited[current] = true;
    queue.push_back(current);
    
    while (!queue.empty()) {
        current = queue.front();
        queue.pop_front();

        for (list<int>::iterator iter = adj[current].begin(); iter != adj[current].end(); ++iter) {
            if (*iter == end) {
                parent[*iter] = current;
                vector<int> path;
                path.push_back(end);
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            if (!visited[*iter]) {
                visited[*iter] = true;
                parent[*iter] = current;
                queue.push_back(*iter);
            }
        }
    }
    return {};
}



int main() {
	ifstream inputFile("input.txt");

	if (!inputFile.is_open()) {
		cerr << "Error opening file." << endl;
	return 1;
	}

	int rows, cols;
	inputFile >> rows >> cols;
	string foo;
	getline(inputFile, foo);
	
	vector<vector<tuple<char, string>>> grid(rows, vector<tuple<char, string>>(cols));

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			string input;
			inputFile >> input;
			grid[i][j] = make_tuple(input[0], input.substr(input.find('-') + 1));
		}
	}
	
	inputFile.close();
	
	Graph graph(rows*cols);
	for (int i=0; i<rows; i++){
    		for (int j=0; j<cols; j++){
    			int tempi = i;
			int tempj = j;
    			if ((get<1>(grid[i][j]) == "E")&&(j!=cols-1)){
    				for (int k=j+1; k<cols; ++k){
    					if (get<0>(grid[i][k]) != get<0>(grid[i][j])){
    						graph.addEdge(i*cols+j, i*cols+k);
    					}
    				}
    			}

    		if ((get<1>(grid[i][j]) == "W")&&(j!=0)){
    			for (int k=j-1; k>=0; --k){
    				if (get<0>(grid[i][k]) != get<0>(grid[i][j])){
                        		graph.addEdge(i*cols+j, i*cols+k);
    				}
    			}
    		}

    		if ((get<1>(grid[i][j]) == "S")&&(i!=rows-1)){
    			for (int k=i+1; k<rows; ++k){
    				if (get<0>(grid[k][j]) != get<0>(grid[i][j])){
    					graph.addEdge(i*cols+j, k*cols+j);
    				}
    			}
    		}

    		if ((get<1>(grid[i][j]) == "N")&&(i!=0)){
    			for (int k=i-1; k>=0; --k){
    				if (get<0>(grid[k][j]) != get<0>(grid[i][j])){
    					graph.addEdge(i*cols+j, k*cols+j);
    				}
    			}
    		}

    		if ((get<1>(grid[i][j]) == "SE")&&(i!=rows-1)&&(j!=cols-1)){
    			while((i<rows-1)&&(j<cols-1)){
    				if (get<0>(grid[i+1][j+1]) != get<0>(grid[tempi][tempj])){
    					graph.addEdge(tempi*cols+tempj, i*cols+cols+j+1);
    				} 
    				i++;
    				j++;
    			}
    		}
    		i = tempi;
    		j = tempj;
    		
    		if ((get<1>(grid[i][j]) == "NW")&&(i!=0)&&(j!=0)){
    			while((i>0)&&(j>0)){
    				if (get<0>(grid[i-1][j-1]) != get<0>(grid[tempi][tempj])){
    					graph.addEdge(tempi*cols+tempj, i*cols-cols+j-1);
    				} 
    				i--;
    				j--;
    			}
    		}
    		i = tempi;
    		j = tempj;
    		
    		if ((get<1>(grid[i][j]) == "NE")&&(i!=0)&&(j!=cols-1)){
    			while((i>0)&&(j<cols-1)){
    				if (get<0>(grid[i-1][j+1]) != get<0>(grid[tempi][tempj])){
    					graph.addEdge(tempi*cols+tempj, i*cols-cols+j+1);
    				} 
    				i--;
    				j++;
    			}
    		}
    		i = tempi;
    		j = tempj;
    		
    		if ((get<1>(grid[i][j]) == "SW")&&(i!=rows-1)&&(j!=0)){
    			while((i<rows-1)&&(j>0)){
    				if (get<0>(grid[i+1][j-1]) != get<0>(grid[tempi][tempj])){
    					graph.addEdge(tempi*cols+tempj, i*cols+cols+j-1);
    				} 
    				i++;
    				j--;
    			}
    		}
    		i = tempi;
    		j = tempj;
    	}
    }

    vector<int> path = graph.findPath(0, rows*cols-1);
    
    ofstream outputFile("output.txt");
    for (int k=0; k < path.size()-1; k++){
    	int i1; int j1; int i2; int j2;
    	
    	j1 = path[k] % cols;
    	i1 = (path[k] - j1)/cols;
    	j2 = path[k+1] % cols;
    	i2 = (path[k+1] - j2)/cols;
    	int i_dif = abs(i2 - i1);
    	int j_dif = abs(j2 - j1);
    	
    	if (i_dif!=0){
    		outputFile << i_dif << get<1>(grid[i1][j1]) << " ";
    	}
    	else{
    		outputFile << j_dif << get<1>(grid[i1][j1]) << " ";
    	}	
    }
    outputFile.close();
    
    
    return 0;         
}


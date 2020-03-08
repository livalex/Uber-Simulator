// Copyright[2019] <Livadaru Alexandru-Valentin 313CA>

#ifndef GRAPH_H_
#define GRAPH_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <queue>

template <typename Tvalue>
class Graph{
 public:
	std::vector<std::vector<int>> matrix;
	int size;

	explicit Graph(const int size) {
		this->size = size;
		matrix.resize(size);
		int j;
			for (j = 0; (unsigned)j < matrix.size(); ++j) {
				matrix[j].resize(size);
		}
	}

	Graph() {
		this->size = 0;
	}

	~Graph() { }

	void set_size(int size) {
		this->size = size;
		matrix.resize(size);
		int j;
			for (j = 0; (unsigned)j < matrix.size(); ++j) {
				matrix[j].resize(size);
		}
	}

	void addEdge(int line, int column) {
		matrix[line][column] = 1;
	}

	void removeEdge(int line, int column) {
		matrix[line][column] = 0;
	}

	bool hasEdge(int line, int column) {
		if (matrix[line][column] == 1) {
			return true;
		}
		return false;
	}

	int BFS(Tvalue beginning, Tvalue ending, int N) {
		std::vector<int> distance(N, -1);
		bool visited[size] = {false};
		std::queue<int> q;
		q.push(beginning);
		visited[beginning] = true;
		distance[beginning] = 0;
		while (q.empty() == false) {
			Tvalue currentVertex = q.front();
			q.pop();
			int i;
			for (i = 0; (unsigned)i < matrix[currentVertex].size(); ++i) {
				if (matrix[currentVertex][i] != 0) {
					if (i == ending && !visited[i]) {
						visited[i] = true;
						distance[i] = distance[currentVertex] + 1;
						return distance[i];
					}
					if (visited[i] == false) {
						q.push(i);
						visited[i] = true;
						distance[i] = distance[currentVertex] + 1;
					}
				}
			}
		}
		if (beginning != ending) {
			return -1;
		} else {
			return 0;
		}
	}
};
#endif  // GRAPH_H_

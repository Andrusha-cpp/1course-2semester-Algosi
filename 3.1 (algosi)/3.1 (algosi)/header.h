#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class graph
{
private:
	vector<vector<int>> adj_matrix;
	vector<bool> exist;
public:
	void addVertex()
	{
		for (int i = 0; i < adj_matrix.size(); i++)
			adj_matrix[i].push_back(0);
		adj_matrix.push_back(vector<int>(adj_matrix.size() + 1, 0));
	}

	void addEdge(int A, int B)
	{
		if (A >= adj_matrix.size() || B >= adj_matrix.size())
		{
			cout << "Wrong index.(" << endl;
			return;
		}
		adj_matrix[A][B] = 1;
	}

	void show()
	{
		cout << "Adj matrix:" << endl;
		for (int i = 0; i < adj_matrix.size(); i++)
		{
			for (int j = 0; j < adj_matrix.size(); j++)
				cout << adj_matrix[i][j] << " ";
			cout << endl;
		}
	}

	void dfsAction(int vertex, vector<bool>& visited)
	{
		visited[vertex] = true;
		cout << vertex << " ";
		for (int i = 0; i < adj_matrix[vertex].size(); ++i)
			if (adj_matrix[vertex][i] && !visited[i])
				dfsAction(i, visited);
	}

	//search in depth
	void dfs(int start)
	{
		vector<bool> visited(adj_matrix.size(), false);
		cout << "DFS: ";
		dfsAction(start, visited);
		cout << endl;
	}

	//search in width
	void bfs(int start)
	{
		int n = adj_matrix.size();
		vector<bool> visited(n, false);
		queue<int> q;  // queue of vertex
		q.push(start); // begin with start
		visited[start] = true;

		cout << "BFS: ";
		while (!q.empty()) {
			int v = q.front(); // take first vertex
			q.pop();
			cout << v << " ";

			// check all vertex
			for (int i = 0; i < n; ++i) {
				//if existing edge and vertex not visited
				if (adj_matrix[v][i] && !visited[i]) {
					visited[i] = true;
					q.push(i);
				}
			}
		}
		cout << endl;
	}

	bool CheckOnConnect() {
		int n = adj_matrix.size();
		if (n == 0)
			return true; //empty graph is connected

		vector<bool> visited(n, false);
		dfsAction(0, visited);

		for (int i = 0; i < visited.size(); i++) {
			if (!visited[i])
				return false;
		}
		return true;
	}

	void extract(fstream& datafile)
	{
		int size;
		datafile >> size;
		for (int i = 0; i < size; i++)
			addVertex();
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				datafile >> adj_matrix[i][j];
	}
};
#include "header.h"

int main() {
	graph connect_graph;
	fstream datafile("data.txt");
	connect_graph.extract(datafile);

	if (connect_graph.CheckOnConnect())
		cout << "Graph is connected." << endl;
	else
		cout << "Graph isn't connected." << endl;

	for (int i = 0; i < 3; i++)
		connect_graph.addVertex();

	connect_graph.addEdge(1, 4); //1-4
	connect_graph.addEdge(4, 1);
	connect_graph.addEdge(4, 5); //4-5
	connect_graph.addEdge(5, 4);
	connect_graph.addEdge(4, 6);//4-6
	connect_graph.addEdge(6, 4);
	connect_graph.addEdge(6, 2);//6-2
	connect_graph.addEdge(2, 6);

	connect_graph.dfs(1);
	connect_graph.bfs(1);

	connect_graph.show();

	datafile.close();
}
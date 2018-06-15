
#include "stdafx.h"
#include "testGraph.h"



int main()
{
	Graph<const char*, int> graph(7);
	const char* vertex[7] = { "地大", "武大", "华科 ", 
		"交大 ", "北大 ", "清华 ", "复旦" };
	for (size_t i = 0; i < 7; i++)
	{
		graph.insertVertex(vertex[i]);
	}
	cout << "----->图的初始化：======================================\n";
	graph.printGraph();

	cout << "图中的顶点数目：" << graph.getNumVertex() << endl;

	int edge[7][3] = { { 0, 1, 43 }/*地大到武大的距离*/,{ 0, 2, 12 },{ 1, 2, 38 },{ 2, 3 ,1325 },
	{ 3, 6, 55 },{ 4, 5, 34 },{ 4, 6, 248 } };    //分配距离
	for (size_t i = 0; i < 7; i++)
	{
		graph.insertEdge(edge[i][0], edge[i][1], edge[i][2]);
		graph.insertEdge(edge[i][1], edge[i][0], edge[i][2]);
	}
	cout << "添加边之后的图结构：============" << endl;
	graph.printGraph();
	system("color  0A");
	return 1;
}


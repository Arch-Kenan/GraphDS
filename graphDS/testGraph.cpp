
//#include "stdafx.h"
//#include "testGraph.h"



//int main()
//{
//	Graph<const char*, int> graph(7);
//	const char* vertex[7] = { "�ش�", "���", "���� ", 
//		"���� ", "���� ", "�廪 ", "����" };
//	for (size_t i = 0; i < 7; i++)
//	{
//		graph.insertVertex(vertex[i]);
//	}
//	cout << "----->ͼ�ĳ�ʼ����======================================\n";
//	graph.printGraph();
//
//	cout << "ͼ�еĶ�����Ŀ��" << graph.getNumVertex() << endl;
//
//	int edge[7][3] = { { 0, 1, 43 }/*�ش����ľ���*/,{ 0, 2, 12 },{ 1, 2, 38 },{ 2, 3 ,1325 },
//	{ 3, 6, 55 },{ 4, 5, 34 },{ 4, 6, 248 } };    //�������
//	for (size_t i = 0; i < 7; i++)
//	{
//		graph.insertEdge(edge[i][0], edge[i][1], edge[i][2]);
//		graph.insertEdge(edge[i][1], edge[i][0], edge[i][2]);
//	}
//	cout << "��ӱ�֮���ͼ�ṹ��============" << endl;
//	graph.printGraph();
//	system("color  0A");
//	return 1;
//}

#include "stdafx.h"
#include "testGraph.h"


using namespace std;

//
//int main()
//{
//	std::pair<int, int>  mk;
//	Graph graph(7);
//	
//
//	//std::vector<std::string>  vertex = { "�ش�", "���", "���� ",
//	//	"���� ", "���� ", "�廪 ", "����" };
//	const char*  vertex[7] = { "�ش�", "���", "���� ",
//		"���� ", "���� ", "�廪 ", "����" };
//	for (size_t i = 0; i < 7; i++)
//	{
//		graph.insertVertex(vertex[i]);
//	}
//
//	int edge[7][3] = { { 0, 1, 43 },{ 0, 2, 12 },{ 1, 2, 38 },{ 2, 3 ,1325 },
//	{ 3, 6, 55 },{ 4, 5, 34 },{ 4, 6, 248 } };    //�������
//	for (size_t i = 0; i < 7; i++)
//	{
//		graph.insertEdge(edge[i][0], edge[i][1], edge[i][2]);
//	}
//	graph.print();
//	/*std::cout<<graph.pVertexTable[3].name;*/
//
//	//const char* name = "kkk";
//	//graph.insertVertex(name);
//	////std::string name(vertex[1]);
//	////std::string test(name);
//	////std::cout << test.c_str();
//	return 0;
//}

int main()
{
	Graph< char, int>   G(5);
	char name[5] = { 'A', 'B', 'C', 'D', 'E' };
	int dist[8][3] = { { 0, 1, 433 },{ 0, 2, 124 },{ 1, 2, 385 },{ 1,4, 248 },{ 2, 3 ,1325 },{ 2, 4, 248 },
	{ 3, 4, 554 },{ 0, 3, 279 } };
	for (size_t i = 0; i < 5; i++)
	{
		G.insertVertex(name[i]);
	}

	for (size_t i = 0; i < 8; i++)
	{
		G.insertEdge(dist[i][0], dist[i][1], dist[i][2]);
		G.insertEdge(dist[i][1], dist[i][0], dist[i][2]);
	}

	int ret;
	G.dijkstra(0, 4, ret);
	//std::cout << ret;

	return 0;
}


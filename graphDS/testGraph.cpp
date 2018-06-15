
#include "stdafx.h"
#include "testGraph.h"



int main()
{
	Graph<const char*, int> graph(7);
	const char* vertex[7] = { "�ش�", "���", "���� ", 
		"���� ", "���� ", "�廪 ", "����" };
	for (size_t i = 0; i < 7; i++)
	{
		graph.insertVertex(vertex[i]);
	}
	cout << "----->ͼ�ĳ�ʼ����======================================\n";
	graph.printGraph();

	cout << "ͼ�еĶ�����Ŀ��" << graph.getNumVertex() << endl;

	int edge[7][3] = { { 0, 1, 43 }/*�ش����ľ���*/,{ 0, 2, 12 },{ 1, 2, 38 },{ 2, 3 ,1325 },
	{ 3, 6, 55 },{ 4, 5, 34 },{ 4, 6, 248 } };    //�������
	for (size_t i = 0; i < 7; i++)
	{
		graph.insertEdge(edge[i][0], edge[i][1], edge[i][2]);
		graph.insertEdge(edge[i][1], edge[i][0], edge[i][2]);
	}
	cout << "��ӱ�֮���ͼ�ṹ��============" << endl;
	graph.printGraph();
	system("color  0A");
	return 1;
}


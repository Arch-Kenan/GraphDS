
//#include "stdafx.h"
//#include "testGraph.h"



//int main()
//{
//	Graph<const char*, int> graph(7);
//	const char* vertex[7] = { "地大", "武大", "华科 ", 
//		"交大 ", "北大 ", "清华 ", "复旦" };
//	for (size_t i = 0; i < 7; i++)
//	{
//		graph.insertVertex(vertex[i]);
//	}
//	cout << "----->图的初始化：======================================\n";
//	graph.printGraph();
//
//	cout << "图中的顶点数目：" << graph.getNumVertex() << endl;
//
//	int edge[7][3] = { { 0, 1, 43 }/*地大到武大的距离*/,{ 0, 2, 12 },{ 1, 2, 38 },{ 2, 3 ,1325 },
//	{ 3, 6, 55 },{ 4, 5, 34 },{ 4, 6, 248 } };    //分配距离
//	for (size_t i = 0; i < 7; i++)
//	{
//		graph.insertEdge(edge[i][0], edge[i][1], edge[i][2]);
//		graph.insertEdge(edge[i][1], edge[i][0], edge[i][2]);
//	}
//	cout << "添加边之后的图结构：============" << endl;
//	graph.printGraph();
//	system("color  0A");
//	return 1;
//}

#include "stdafx.h"
#include "self_practise.h"


using namespace std;


int main()
{
	Graph graph(7);
	

	//std::vector<std::string>  vertex = { "地大", "武大", "华科 ",
	//	"交大 ", "北大 ", "清华 ", "复旦" };
	const char*  vertex[7] = { "地大", "武大", "华科 ",
		"交大 ", "北大 ", "清华 ", "复旦" };
	for (size_t i = 0; i < 7; i++)
	{
		graph.insertVertex(vertex[i]);
	}

	int edge[7][3] = { { 0, 1, 43 },{ 0, 2, 12 },{ 1, 2, 38 },{ 2, 3 ,1325 },
	{ 3, 6, 55 },{ 4, 5, 34 },{ 4, 6, 248 } };    //分配距离
	for (size_t i = 0; i < 7; i++)
	{
		graph.insertEdge(edge[i][0], edge[i][1], edge[i][2]);
	}
	graph.print();
	/*std::cout<<graph.pVertexTable[3].name;*/

	//const char* name = "kkk";
	//graph.insertVertex(name);
	////std::string name(vertex[1]);
	////std::string test(name);
	////std::cout << test.c_str();
	return 0;
}








//class foo
//{
//public:
//	foo() { std::cout << "默认构造函数\n"; };
//	foo(int size) 
//	{
//		name = new char[size + 1];
//		int i = 0;
//		for (  ; i < size; i++)
//		{
//			name[i] = 'k';
//		}
//		name[i] = '\0';
//		std::cout << "构造函数\n";
//	}
//	foo(foo& test)
//	{
//		this->name = test.name;
//		std::cout << "拷贝构造函数\n";
//	}
//	~foo()
//	{
//		delete[] name;
//		std::cout << "析构函数\n";
//	}
//	char* name;
//};
//
//
//int change(foo test)
//{
//	
//	return 1;
//}
//
//void change(std::string& name1)
//{
//	std::string local = name1;
//	char* pbuffer = const_cast<char*>(local.c_str());
//	pbuffer[1] = 'A';
//}
//
//void testStr(const char* name)
//{
//	std::cout << name;
//}
//
//int main()
//{
//	foo test(10);
//	//change(test);
//	std::cout << test.name;
//	return 0;
//
//}
#include "windows.h"
#include <stdio.h> 
#include "iostream"
#include "vector"
#include "algorithm"
#include "math.h"  
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdio.h>   

using namespace std;

template<class DistType/*边的权值的类型*/>
class Edge//边的定义
{
public:
	Edge(int dest, DistType weight)
	{
		m_nposTable = dest;
		m_distWeight = weight;
		m_pnext = NULL;
	}
	~Edge()
	{

	}
public:
	int m_nposTable;//该边的目的顶点在顶点集中的位置
	DistType m_distWeight;//边的权重值
	Edge<DistType> *m_pnext;//下一条边（注意不是下一个顶点，因为m_nposTable已经知道了这个顶点的位置）
};
//声明
template<class NameType/*顶点集名字类型*/, class DistType/*距离的数据类型*/> class Graph;

template<class NameType/*顶点集名字类型*/, class DistType/*距离的数据类型*/>
class Vertex//顶点的定义
{
public:
	Vertex()
	{
		padjEdge = NULL;
		m_vertexName = 0;
	}
	~Vertex()
	{
		Edge<DistType> *pmove = padjEdge;
		while (pmove)
		{
			padjEdge = pmove->m_pnext;
			delete pmove;
			pmove = padjEdge;
		}
	}

private:
	friend class Graph<NameType, DistType>;//允许Graph类任意访问
	NameType m_vertexName;//顶点中的数据内容
	Edge<DistType> *padjEdge;//顶点的邻边

};


template<class NameType/*顶点集名字类型*/, class DistType/*距离的数据类型*/>
class Graph
{
public:
	Graph(int size = m_nDefaultSize/*图顶点集的规模*/)
	{
		m_pVertexTable = new Vertex<NameType, DistType>[size];  //为顶点集分配内存
		if (m_pVertexTable == NULL)
		{
			exit(1);
		}
		m_numVertexs = 0;
		m_nmaxSize = size;
		m_nnumEdges = 0;
	}

	~Graph()
	{
		Edge<DistType> *pmove;
		for (int i = 0; i < this->m_numVertexs; i++)
		{
			pmove = this->m_pVertexTable[i].padjEdge;
			if (pmove) {
				this->m_pVertexTable[i].padjEdge = pmove->m_pnext;
				delete pmove;
				pmove = this->m_pVertexTable[i].padjEdge;
			}
		}
		delete[] m_pVertexTable;
	}
	int GetNumEdges()
	{
		return m_nnumEdges / 2;
	}
	int GetNumVertexs()
	{
		return m_numVertexs;
	}
	bool IsGraphFull() const
	{     //图满的?
		return m_nmaxSize == m_numVertexs;
	}
	//在顶点集中位置为v1和v2的顶点之间插入边
	bool InsertEdge(int v1, int v2, DistType weight = m_Infinity);
	bool InsertVertex(const NameType vertex);   //插入顶点名字为vertex的顶点
	void PrintGraph();   //打印图
private:
	Vertex<NameType, DistType> *m_pVertexTable;   //顶点集
	int m_numVertexs;//图中当前的顶点数量
	int m_nmaxSize;//图允许的最大顶点数
	static const int m_nDefaultSize = 10;       //默认的最大顶点集数目
	static const DistType m_Infinity = 65536;  //边的默认权值（可以看成是无穷大）
	int m_nnumEdges;//图中边的数目
	int GetVertexPosTable(const NameType vertex);    //用该顶点的名字来寻找其在顶点集中的位置
};


//返回顶点vertexname在m_pVertexTable(顶点集)中的位置
//如果不在顶点集中就返回-1
template<class NameType, class DistType>
int Graph<NameType, DistType>::GetVertexPosTable(const NameType vertexname)
{
	for (int i = 0; i < this->m_numVertexs; i++)
	{
		if (vertexname == m_pVertexTable[i].m_vertexName)
		{
			return i;
		}
	}
	return -1;
}

//打印图中的各个顶点及其链接的边的权重
template<class NameType, class DistType>
void Graph<NameType, DistType>::PrintGraph()
{
	Edge<DistType> *pmove;
	for (int i = 0; i<this->m_numVertexs; i++)
	{
		cout << this->m_pVertexTable[i].m_vertexName << "--->";
		pmove = this->m_pVertexTable[i].padjEdge;
		while (pmove)
		{
			cout << pmove->m_distWeight << "--->" << this->m_pVertexTable[pmove->m_nposTable].m_vertexName << "--->";
			pmove = pmove->m_pnext;
		}
		cout << "NULL" << endl;
	}
}


//顶点依次插入到分配好的顶点集中
template<class NameType, class DistType>
bool Graph<NameType, DistType>::InsertVertex(const NameType vertexname)
{
	if (IsGraphFull())
	{
		cerr << "图已经满，请勿再插入顶点！" << endl;
		return false;
	}
	else
	{
		this->m_pVertexTable[this->m_numVertexs].m_vertexName = vertexname;
		this->m_numVertexs++;
	}

	return true;
}

//在顶点集位置为v1和v2的顶点之间插入权值为weght的边（务必保持输入的准确性，否则.....）
template<class NameType, class DistType>
bool Graph<NameType, DistType>::InsertEdge(int v1, int v2, DistType weight)
{
	if (v1 < 0 && v1 > this->m_numVertexs && v2 < 0 && v2 > this->m_numVertexs)
	{
		cerr << "边的位置参数错误，请检查！ " << endl;
		return false;
	}
	else
	{
		Edge<DistType> *pmove = m_pVertexTable[v1].padjEdge;
		if (pmove == NULL)//如果顶点v1没有邻边
		{ //建立顶点v1的第一个邻边(该邻边指明了目的顶点)
			m_pVertexTable[v1].padjEdge = new Edge<DistType>(v2, weight);
			m_nnumEdges++;//图中边的数目
			return true;
		}
		else//如果有邻边
		{
			while (pmove->m_pnext)
			{
				pmove = pmove->m_pnext;
			}
			pmove->m_pnext = new Edge<DistType>(v2, weight);
			m_nnumEdges++;//图中边的数目
			return true;
		}
	}
}
#pragma once
#include <iostream>
#include <Windows.h>
#include <queue>
using namespace std;


template <typename DistType>
class Edge
{
public:
	Edge(int index, DistType weight)
	{
		m_posTable = index;
		m_weight = weight;
		m_next = nullptr;
	}
	~Edge()
	{

	}
	//重载
	friend bool operator < (Edge& edge1, Edge& edge2)
	{
		return edge1.m_weight < edge2.m_weight;
	}
public:
	int m_posTable;//目的顶点所在顶点集中的位置
	DistType m_weight;//边的的权值
	Edge<DistType>* m_next;//下一条边
};



template <typename NameType, typename DistType> class Graph;
template <typename NameType, typename DistType>
class Vertex
{
public:
	Vertex()
	{
		m_adjcentEdge = nullptr;
		m_vertexName = 0;
	}
	~Vertex()
	{
		Edge<DistType> *pmove =this->m_adjcentEdge;
		while (pmove)
		{
			m_adjcentEdge = pmove->m_next;
			delete pmove;
			pmove = m_adjcentEdge;
		}
	}
private:
	friend class Graph<NameType, DistType>;
	NameType m_vertexName;
	Edge<DistType>* m_adjcentEdge;//顶点的邻边
};



template <typename NameType, typename DistType>
class Graph
{
public:
	Graph(int size = m_defaultSize )
	{
		m_VertxTable = new Vertex<NameType, DistType>[size];
		if (m_VertxTable == nullptr)
		{
			exit(1);
		}
		m_numVertexs = 0;
		m_numEdges = 0;
		m_maxSize = size;
	}
	~Graph()
	{
		Edge<DistType> *pmove;
		for (size_t i = 0; i < this->m_numVertexs; i++)
		{
			pmove = this->m_VertxTable[i].m_adjcentEdge;
			while (pmove)
			{
				this->m_VertxTable[i].m_adjcentEdge = pmove->m_next;
				delete pmove;
				pmove = this->m_VertxTable[i].m_adjcentEdge;
			}
		}
		delete[] m_VertxTable;
	}
	int getNumVertex()
	{
		return this->m_numVertexs;
	}
	int getNumEdges()
	{
		return this->m_numEdges / 2;
	}
	bool isGraphFull()
	{
		return m_numVertexs == m_maxSize;
	}
	//插入顶点名字为vertex的顶点
	bool insertVertex(const NameType vertexName)
	{
		if (isGraphFull())
		{
			cerr << "图已经满了， 请勿再插入顶点！\n";
			return false;
		}
		else
		{
			this->m_VertxTable[this->m_numVertexs].m_vertexName = vertexName;
			this->m_numVertexs++;
		}
		return true;
	}

	//在顶点中位置为p1和p2的顶点之间插入边
	bool insertEdge(int p1, int p2, DistType weight = m_infinite)
	{
		if (p1 <0 && p2 > this->m_numVertexs && p2 <0 && p2>this->m_numVertexs)
		{
			cerr << "边的位置参数设置错误， 请检查！\n";
			return false;
		}
		else
		{
			Edge<DistType>* pmove = m_VertxTable[p1].m_adjcentEdge;
			if (pmove == nullptr)//如果顶点p1没有邻边
			{
				//将p2接入p1的后面
				m_VertxTable[p1].m_adjcentEdge = new Edge<DistType>(p2, weight);
				m_numEdges++;
				return true;
			}
			else
			{
				while (pmove->m_next)
				{
					pmove = pmove->m_next;
				}
				pmove->m_next = new Edge<DistType>(p2, weight);
				m_numEdges++;
				return true;
			}
		}
	}
	//打印图中各个顶点及其链接边的权重
	void printGraph()
	{
		Edge<DistType> *pmove;
		for (size_t i = 0; i < this->m_numVertexs; i++)
		{
			cout << this->m_VertxTable[i].m_vertexName << "---->";
			pmove = this->m_VertxTable[i].m_adjcentEdge;
			while (pmove)
			{
				cout << pmove->m_weight << "---->" << this->m_VertxTable[pmove->m_posTable].m_vertexName << "---->";
				pmove = pmove->m_next;
			}
			cout << "顶点所邻接的边已经输入完毕；\n";
		}
	}
	bool dijkstra(int v1, int v2, DistType& result)
	{
		typedef std::pair< DistType, int> mkPair;
		priority_queue<mkPair, vector<mkPair>, greater<mkPair> >    Queue;
		int        path[m_defaultSize] = { 0 };
		DistType   resultArrs[m_defaultSize];
		for (size_t i = 0; i < 5; i++)
		{
			resultArrs[i] = INT_MAX;
		}

		//开始访问
		Edge<DistType>*    arcEdge = this->m_VertxTable[v1].m_adjcentEdge;
		while (arcEdge)
		{
			resultArrs[arcEdge->m_posTable] = arcEdge->m_weight;
			Queue.push(mkPair(arcEdge->m_weight, arcEdge->m_posTable));
			arcEdge = arcEdge->m_next;
		}

		//Ñ­»·²Ù×÷
		while (!Queue.empty())
		{
			mkPair  topForest = Queue.top();
			Queue.pop();
			DistType   w = topForest.first;
			Edge<DistType>*    e = this->m_VertxTable[topForest.second].m_adjcentEdge;

			while (e)
			{
				//防止反复计算路径
				if (e->m_posTable == v1)
				{
					e = e->m_next;
					continue;
				}
				if (w + e->m_weight < resultArrs[e->m_posTable])
				{
					resultArrs[e->m_posTable] = w + e->m_weight;
					path[e->m_posTable] = topForest.second;
					Queue.push(mkPair(w + e->m_weight, e->m_posTable));
				}
				e = e->m_next;
			}

		}
		result = resultArrs[v2];
		do
		{
			std::cout << v2 << "的父亲是:" << path[v2] << std::endl;
			v2 = path[v2];	
		} while (path[v2] != v2);

		return true;
	}
private:

	Vertex<NameType, DistType> *m_VertxTable;//顶点集
	int m_numVertexs;//当前顶点的数量
	int m_maxSize;
	const static int m_defaultSize = 10;
	const static DistType m_infinite = 65536;//边默认最大权值
	int m_numEdges;//图中边的数量

	//用该顶点的名字来寻找其在顶点集中的位置
	int getVertexPostable(const NameType vertexName)
	{
		for (size_t i = 0; i < this->m_numVertexs; i++)
		{
			if (vertexName == this->m_VertxTable[i].m_vertexName)
			{
				return i;
			}
			
		}
		return -1;
	}
};



	


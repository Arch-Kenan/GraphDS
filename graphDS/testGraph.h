#pragma once
#include <iostream>
#include <Windows.h>
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
public:
	int m_posTable;//�ı��Ŀ�Ķ������ڶ��㼯�е�λ��
	DistType m_weight;//�ߵĵ�Ȩֵ
	Edge<DistType>* m_next;//��һ����
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
	Edge<DistType>* m_adjcentEdge;//������ڱ�
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
		//for (size_t i = 0; i < this->m_numVertexs; i++)
		//{
		//	pmove = this->m_VertxTable[i].m_adjcentEdge;
		//	if (pmove)
		//	{
		//		this->m_VertxTable[i].m_adjcentEdge = pmove->m_next;
		//		delete pmove;
		//		pmove = this->m_VertxTable[i].m_adjcentEdge;
		//	}

		//}
		//delete[] m_VertxTable;
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
	//���붥������Ϊvertex�Ķ���
	bool insertVertex(const NameType vertexName)
	{
		if (isGraphFull())
		{
			cerr << "ͼ�Ѿ����ˣ� �����ٲ��붥�㣡\n";
			return false;
		}
		else
		{
			this->m_VertxTable[this->m_numVertexs].m_vertexName = vertexName;
			this->m_numVertexs++;
		}
		return true;
	}

	//�ڶ�����λ��Ϊp1��p2�Ķ���֮������
	bool insertEdge(int p1, int p2, DistType weight = m_infinite)
	{
		if (p1 <0 && p2 > this->m_numVertexs && p2 <0 && p2>this->m_numVertexs)
		{
			cerr << "�ߵ�λ�ò������ô��� ���飡\n";
			return false;
		}
		else
		{
			Edge<DistType>* pmove = m_VertxTable[p1].m_adjcentEdge;
			if (pmove == nullptr)//�������p1û���ڱ�
			{
				//��p2����p1�ĺ���
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
	//��ӡͼ�и������㼰�����ӱߵ�Ȩ��
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
			cout << "�������ڽӵı��Ѿ�������ϣ�\n";
		}
	}
private:

	Vertex<NameType, DistType> *m_VertxTable;//���㼯
	int m_numVertexs;//��ǰ���������
	int m_maxSize;
	const static int m_defaultSize = 10;
	const static DistType m_infinite = 65536;//��Ĭ�����Ȩֵ
	int m_numEdges;//ͼ�бߵ�����

	//�øö����������Ѱ�����ڶ��㼯�е�λ��
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



	


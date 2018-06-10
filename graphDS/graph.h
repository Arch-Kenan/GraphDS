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

template<class DistType/*�ߵ�Ȩֵ������*/>
class Edge//�ߵĶ���
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
	int m_nposTable;//�ñߵ�Ŀ�Ķ����ڶ��㼯�е�λ��
	DistType m_distWeight;//�ߵ�Ȩ��ֵ
	Edge<DistType> *m_pnext;//��һ���ߣ�ע�ⲻ����һ�����㣬��Ϊm_nposTable�Ѿ�֪������������λ�ã�
};
//����
template<class NameType/*���㼯��������*/, class DistType/*�������������*/> class Graph;

template<class NameType/*���㼯��������*/, class DistType/*�������������*/>
class Vertex//����Ķ���
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
	friend class Graph<NameType, DistType>;//����Graph���������
	NameType m_vertexName;//�����е���������
	Edge<DistType> *padjEdge;//������ڱ�

};


template<class NameType/*���㼯��������*/, class DistType/*�������������*/>
class Graph
{
public:
	Graph(int size = m_nDefaultSize/*ͼ���㼯�Ĺ�ģ*/)
	{
		m_pVertexTable = new Vertex<NameType, DistType>[size];  //Ϊ���㼯�����ڴ�
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
	{     //ͼ����?
		return m_nmaxSize == m_numVertexs;
	}
	//�ڶ��㼯��λ��Ϊv1��v2�Ķ���֮������
	bool InsertEdge(int v1, int v2, DistType weight = m_Infinity);
	bool InsertVertex(const NameType vertex);   //���붥������Ϊvertex�Ķ���
	void PrintGraph();   //��ӡͼ
private:
	Vertex<NameType, DistType> *m_pVertexTable;   //���㼯
	int m_numVertexs;//ͼ�е�ǰ�Ķ�������
	int m_nmaxSize;//ͼ�������󶥵���
	static const int m_nDefaultSize = 10;       //Ĭ�ϵ���󶥵㼯��Ŀ
	static const DistType m_Infinity = 65536;  //�ߵ�Ĭ��Ȩֵ�����Կ����������
	int m_nnumEdges;//ͼ�бߵ���Ŀ
	int GetVertexPosTable(const NameType vertex);    //�øö����������Ѱ�����ڶ��㼯�е�λ��
};


//���ض���vertexname��m_pVertexTable(���㼯)�е�λ��
//������ڶ��㼯�оͷ���-1
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

//��ӡͼ�еĸ������㼰�����ӵıߵ�Ȩ��
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


//�������β��뵽����õĶ��㼯��
template<class NameType, class DistType>
bool Graph<NameType, DistType>::InsertVertex(const NameType vertexname)
{
	if (IsGraphFull())
	{
		cerr << "ͼ�Ѿ����������ٲ��붥�㣡" << endl;
		return false;
	}
	else
	{
		this->m_pVertexTable[this->m_numVertexs].m_vertexName = vertexname;
		this->m_numVertexs++;
	}

	return true;
}

//�ڶ��㼯λ��Ϊv1��v2�Ķ���֮�����ȨֵΪweght�ıߣ���ر��������׼ȷ�ԣ�����.....��
template<class NameType, class DistType>
bool Graph<NameType, DistType>::InsertEdge(int v1, int v2, DistType weight)
{
	if (v1 < 0 && v1 > this->m_numVertexs && v2 < 0 && v2 > this->m_numVertexs)
	{
		cerr << "�ߵ�λ�ò����������飡 " << endl;
		return false;
	}
	else
	{
		Edge<DistType> *pmove = m_pVertexTable[v1].padjEdge;
		if (pmove == NULL)//�������v1û���ڱ�
		{ //��������v1�ĵ�һ���ڱ�(���ڱ�ָ����Ŀ�Ķ���)
			m_pVertexTable[v1].padjEdge = new Edge<DistType>(v2, weight);
			m_nnumEdges++;//ͼ�бߵ���Ŀ
			return true;
		}
		else//������ڱ�
		{
			while (pmove->m_pnext)
			{
				pmove = pmove->m_pnext;
			}
			pmove->m_pnext = new Edge<DistType>(v2, weight);
			m_nnumEdges++;//ͼ�бߵ���Ŀ
			return true;
		}
	}
}
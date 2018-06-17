#pragma once

#ifndef SELF_PRACTISE_H
#define SELF_PRACTISE_H

#include <string>
#include <iostream>
#include <vector>


struct Edge
{
	Edge(){ pNext = nullptr; };
	int pos;
	int weight;
	Edge* pNext ;
};


struct Vertex
{
	Vertex() { firstEdge = nullptr; }
	const char*       name;
	Edge*      firstEdge ;
};


struct Graph
{
public:
	Graph(int size)
	{
		this->pVertexTable = new Vertex[size];
		Vertex* ptr = new Vertex[size];
		sizeNum = size;
		vertexIndex = 0;
	}
	bool insertVertex(const char* name1)
	{
		if (vertexIndex < sizeNum)
		{
			this->pVertexTable[this->vertexIndex].name = name1;
			this->vertexIndex++;
			return true;
		}
		else
		{
			std::cerr << "图的空间已经满了\n";
			return false;
		}
	}
	bool insertEdge(int p1, int p2, int weight)
	{
		if (p1 <0 || p1 > sizeNum || p2< 0 || p2 > sizeNum)
		{
			std::cerr << "位置设置不合理\n";
			return false;
		}
		else
		{
			Edge*& firstEdge = this->pVertexTable[p1].firstEdge;

			Edge* pEdge = new Edge;
			pEdge->pos = p2;
			pEdge->weight = weight;
			pEdge->pNext = nullptr;

			if (firstEdge == nullptr)
			{
				firstEdge = pEdge;
			}
			else
			{
				while (firstEdge)
				{
					firstEdge = firstEdge->pNext;
				}
				firstEdge = pEdge;
			}
			return true;
		}
	}
	~Graph()
	{
		delete[] pVertexTable;
	}
	
	bool print()
	{
		for (size_t i = 0; i < this->vertexIndex; i++)
		{
			Vertex  tempVertex = this->pVertexTable[i];

			std::cout << tempVertex.name;

			Edge* tempEdge = tempVertex.firstEdge;
			while (tempEdge != nullptr)
			{
				std::cout << "----->" << tempEdge->weight << this->pVertexTable[tempEdge->pos].name;
				tempEdge = tempEdge->pNext;
			}
			std::cout << std::endl;
		}
		return true;
	}

	int sizeNum;
	int vertexIndex;
	Vertex * pVertexTable;
};




#endif // !SELF_PRACTISE_H


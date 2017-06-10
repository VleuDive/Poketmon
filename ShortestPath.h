#pragma once

#include "GraphType.h"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int INF = 9999;

struct DistanceContainer
{
	int vertex;
	int distance;
};

// �켱���� ť ������ overloading
struct Comp
{
	bool operator() (struct DistanceContainer lhs, struct DistanceContainer rhs)
	{
		return lhs.distance > rhs.distance;
	}
};


void Dijkstra(GraphType* graph, int num_vertex, int** adj, int start, int end, vector<NodeType>& route, int& time);	// �Ÿ� ���� ä���


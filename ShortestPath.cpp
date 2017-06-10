#include "ShortestPath.h"

void Dijkstra(GraphType* graph, int num_vertex, int** adj, int start, int end, vector<NodeType>& route, int& time)
{
	priority_queue<DistanceContainer, vector<DistanceContainer>, Comp> pq;
	struct DistanceContainer c;
	c.vertex = start;
	c.distance = 0;
	pq.push(c);

	int* dist = new int[num_vertex];
	int* path = new int[num_vertex];
	for(int i = 0; i < num_vertex; ++i)
	{
		dist[i] = INF;
		path[i] = -1;
	}
	dist[start] = 0;		//������ ó��
	path[start] = start;	//������ ó��
	
	while(!pq.empty())
	{
		struct DistanceContainer cur_container = pq.top();
		pq.pop();
		
		int cur_vertex = cur_container.vertex;
		for(int i = 0; i < num_vertex; ++i)
		{
			if (adj[cur_vertex][i] > 0)	// ���� �Ǿ� �ִٸ�
			{
				int cur_distance = dist[cur_vertex] + adj[cur_vertex][i];
				if (cur_distance < dist[i])
				{
					dist[i] = cur_distance;
					path[i] = cur_vertex;
					struct DistanceContainer cont;
					cont.vertex = i;
					cont.distance = cur_distance;
					pq.push(cont);
				}
			}
		}
	}

	// cout << "�� �ε��� �ִ� ��� ����" << endl;
	// for(int i = 0; i < num_vertex; ++i)
	// {
	// 	cout << "[" << i << "] : " << dist[i] << endl;
	// }
	// cout << endl;

	if(dist[end] == INF)
		cout << "no route" << endl;
	else
	{
		stack<int> st;
		int next = end;
		while(next != start)
		{
			st.push(next);
			next = path[next];
		}
		st.push(start);

        st.pop();   // ���� ���ؽ��� ����
		while(!st.empty())
		{
			int cur_index = st.top();
			NodeType cur_node = graph->getNodeByIndex(cur_index);
			route.push_back(cur_node);
			// cout << st.top(); 
			st.pop();
            // if(st.size() != 0)
            //     cout << " -> ";
		}
		// cout << endl;
		time += dist[end];
	}
}
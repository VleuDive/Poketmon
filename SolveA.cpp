#include "SolveA.h"

void SolveA::setGraph(GraphType graph)
{
	this->graph = graph;
}


vector<Route> SolveA::getSolutionA()
{
	return all_routes;
}


void SolveA::setProblemA(int specificTime, int specific_poketmon_id)
{
	this->specificTime = specificTime;
	this->specific_poketmon_id = specific_poketmon_id;
}

// sol : route
// ó�� ���� ������ ��尡 ������ Ȯ��( ó�� ��ҷ� ���ƿԴ���)
bool SolveA::promising(vector<NodeType>& sol)
{
	if (sol.size() == 1) return false;
	if (sol.back().index == 0)
	{
		return true;
	}
	return false;
}

// �湮���� ���� ��常 �湮�ϵ��� �ĺ��� �����.
void SolveA::construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand)
{
	vector<int> adj;

	// ���� ������ ��� �� ������ ����� ���� ��� vector
	adj = graph.getAdjacent(sol.back());	 // ������� �ޱ�

	for(int i = 0; i < adj.size(); ++i)
	{
		if(adj[i] == 0) cand.push_back(0);
		else if(!visited[adj[i]]) 
			cand.push_back(adj[i]);
	}
}

// �ϼ��� �� cur_route(ȸ��)�� all_route�� �߰��Ѵ�.
void SolveA::process_solution(vector<NodeType>& sol, int time, int poketmon_counter[])
{
	Route cur_route;
	cur_route.route = sol;
	cur_route.time = time;
	for(int i = 0; i < NUM_POKETMON; ++i)
		cur_route.poketmon_counter[i] = poketmon_counter[i];
	all_routes.push_back(cur_route);
}


void SolveA::backtrack(vector<NodeType>& sol, bool visited[], int time, int poketmon_counter[])
{
	vector<int> cand;

	if ( promising(sol) )
		process_solution(sol, time, poketmon_counter);
	else
	{
		construct_candidates(sol, visited, cand);
		for(int i = 0; i < cand.size(); ++i)
		{
			NodeType cand_Node;
			cand_Node.index = cand[i];
			sol.push_back(cand_Node);
			visited[cand[i]] = true;
			time += graph.WeightIs(sol[sol.size()-2], sol[sol.size()-1]);
			if(cand[i] != 0 )
				poketmon_counter[cand[i]]++;

			backtrack(sol, visited, time, poketmon_counter);

			time -= graph.WeightIs(sol[sol.size()-2], sol[sol.size()-1]);
			if(cand[i] != 0 )
				poketmon_counter[cand[i]]--;
			sol.pop_back();
			visited[cand[i]] = false;
		}
	}
}


// ��� ȸ�θ� �����.
void SolveA::make_all_route()
{
	vector<NodeType> sol;
	sol.push_back(graph.getNodeByIndex(0));
	bool visited[MAX_NODE];
	visited[0] = true;
	for(int i = 1; i < MAX_NODE; ++i)
		visited[i] = false;
	specificTime = 0;
	for(int i = 0; i < NUM_POKETMON; ++i)
		poketmon_counter[i]  = 0;
	backtrack(sol, visited, specificTime, poketmon_counter);
}

void SolveA::find_solution()
{
	make_all_route();

	for(int i = 0; i < all_routes.size(); ++i)
	{
		cout << "Route " << i << " : ";
		for(int j = 0; j < all_routes[i].route.size(); ++j)
		{
			cout << all_routes[i].route[j].index << " ";
		}
		cout << endl;
		/*cout << "Poketmon counter of Route " << i << " : ";
		for(int j = 0; j < NUM_POKETMON; ++j)
		{
			cout << "[" << j << "]" << all_routes[i].poketmon_counter[j] << " ";
		}*/
		cout << "Time of Route : " << all_routes[i].time;
		cout << endl;
	}

	/*int big = 0;
	int big_route_index = 0;
	for(int i = 0; i < all_routes.size(); ++i)
	{
		if(all_routes[i].poketmon_counter[specific_poketmon_id] > big
			&& all_routes[i].time <= specificTime)
		{	
			big = all_routes[i].poketmon_counter[specific_poketmon_id];
			big_route_index = i;
		}
	}

	for(int i = 0; i < all_routes[big_route_index].route.size(); ++i)
	{
		cout << all_routes[big_route_index].route[i].index << " ";
	}*/
}



#ifndef MANYMONSCATCH_H
#define MANYMONSCATCH_H
#include "graphtype.h"
#include "selectalgorithm.h"
#define MAX_NODE 100
#define MAX_CANDIDATES 12
#define NUM_ID 12

#define START_VERTEX 0
#define START_ID 0
#define POKETSTOP_ID 11

class ManyMonsCatch : public SelectAlgorithm
{
private:
    QVector<Route> all_solution_routes;
    Route best_route;
    QVector<QVector<int> > map_of_id_to_node_index_list;	// map(Poketmon_id -> node_index_list)
    int specific_time;
    QVector<int> poketStop_node_index_list;
public:
    ManyMonsCatch();
    QVector<QString> FindRoute();
    void SetProblem(QVector<int> data);
    void setGraph(GraphType* gr);
    void backtrack(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int num_poketball, int poketStop_time[]);
    bool promising(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon);
    void process_solution(QVector<NodeType>& sol, int time, int num_catch_poketmon);
    void construct_candidates(QVector<NodeType>& sol, bool visited[], QVector<int>& cand);
    void update_poketStop_state(bool visited[], int poketStop_time[], int consuming_time, int mode);

};

#endif // MANYMONSCATCH_H

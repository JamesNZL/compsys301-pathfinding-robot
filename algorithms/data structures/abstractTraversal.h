#ifndef ABSTRACTTRAVERSAL_H
#define ABSTRACTTRAVERSAL_H
#include "../utils/outputs.h"
#include "graph.h"
using namespace std;

class AbstractTraversal {
public:
    AbstractTraversal() {}
    AbstractTraversal(Graph graph){

    };
    virtual void findShortestPath(pair<int, int> start, pair<int, int> end) = 0;
    Graph graph;
    vector<pair<int, int>> shortestPath;

private:
};

#endif
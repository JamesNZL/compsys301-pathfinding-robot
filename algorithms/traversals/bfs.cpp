#include "../data structures/abstractTraversal.h"
#include "../data structures/graph.h"
#include "../utils/indexConversion.h"
#include "../utils/outputs.h"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class GraphBFS : public AbstractTraversal {
public:
    GraphBFS(Graph _graph) {
        graph = _graph;
    }

    void findShortestPath(pair<int, int> start, pair<int, int> end) override {
        // Conversions
        int w = graph.mazeWidth;
        int h = graph.mazeHeight;
        int start1dCoord = pairTo1d(start, h, w);
        int end1dCoord = pairTo1d(end, h, w);
        unordered_map<int, vector<int>> adjList = graph.adjList;
        // Required data structures
        queue<int> q;
        unordered_map<int, int> pred;
        vector<bool> visited(w * h, false);

        q.push(start1dCoord);
        visited[start1dCoord] = true;
        int current;
        while (!q.empty()) {
            current = q.front();
            q.pop();
            cout << current << "\n";
            if (current == end1dCoord) {
                break;
            }
            for (int neighbour : adjList[current]) {
                if (!visited[neighbour]) {
                    visited[neighbour] = true;
                    pred[neighbour] = current;
                    q.push(neighbour);
                }
            }
        }

        // recreate path from end to start LIFO
        stack<int> stack;
        stack.push(current);
        while (current != start1dCoord) {
            current = pred[current];
            stack.push(current);
        }

        while (!stack.empty()) {
            pair<int, int> coord2d = convertToXY(stack.top(), h, w);
            shortestPath.push_back(coord2d);
            stack.pop();
        }
    }
    void printShortestPath() override {
        for (pair<int, int> coords : shortestPath) {
            cout << "(" << coords.first << "," << coords.second << ")"
                 << " ";
        }
    }

    vector<pair<int, int>> shortestPath;

private:
    Graph graph;
};

int main() {
    int startX, startY, endX, endY;
    Graph testGraph("../maps/map_1.txt");
    GraphBFS testBFS(testGraph);
    printMaze(testGraph.maze);
    printAdjList(testGraph.adjList);
    // start BFS
    pair<int, int> start = make_pair<int, int>(1, 1);
    pair<int, int> end = make_pair<int, int>(17, 1);
    if (!(testGraph.isValidCoords(start) && testGraph.isValidCoords(end))) {
        cerr << "invalid coordinates";
        throw exception();
    }
    testBFS.findShortestPath(start, end);
    testBFS.printShortestPath();
    exportPathToFile(testGraph, testBFS.shortestPath);
    return 0;
}
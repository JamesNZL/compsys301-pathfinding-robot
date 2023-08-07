#include "../data structures/graph.h"
#include "../utils/indexConversion.h"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

typedef pair<int, int> Coords;

class GraphBFS {
public:
    GraphBFS(Graph _graph) {
        graph = _graph;
    }

    void findShortestPath(Coords start, Coords end) {
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
            if (current == end1dCoord)
                break;
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
            Coords coord2d = convertToXY(stack.top(), h, w);
            shortestPath.push_back(coord2d);
            stack.pop();
        }
    }
    void printShortestPath() {
        for (Coords coords : shortestPath) {
            cout << "(" << coords.first << "," << coords.second << ")"
                 << " ";
        }
    }

private:
    Graph graph;
    vector<Coords> shortestPath;
};

int main() {
    Graph testGraph("../maps/map_1.txt");
    testGraph.printMaze();
    GraphBFS testBFS(testGraph);
    // start BFS
    Coords start = make_pair<int, int>(1, 1);
    Coords end = make_pair<int, int>(1, 17);
    testBFS.findShortestPath(start, end);
    testBFS.printShortestPath();
    return 0;
}
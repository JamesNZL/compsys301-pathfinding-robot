#include "../data structures/abstractTraversal.h"
#include "../data structures/graph.h"
#include "../utils/indexConversion.h"
#include "../utils/outputs.h"
#include "../utils/pathToTurns.h"
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

    vector<pair<int, int>> shortestPath;

private:
    Graph graph;
};

int main() {
    int startX, startY, endX, endY;
    cout << "Enter starting point x:";
    cin >> startX;
    cout << "Enter starting point y:";
    cin >> startY;
    cout << "Enter destination x:";
    cin >> endX;
    cout << "Enter destination y:";
    cin >> endY;

    int directionInt;
    Direction startingDirection;
    cout << "Enter the direction (0 for UP, 1 for DOWN, 2 for LEFT, 3 for RIGHT): ";
    cin >> directionInt;
    switch (directionInt) {
    case 0:
        startingDirection = UP;
        break;
    case 1:
        startingDirection = DOWN;
        break;
    case 2:
        startingDirection = LEFT;
        break;
    case 3:
        startingDirection = RIGHT;
        break;
    default:
        cout << "Invalid input. Using default value: UP." << std::endl;
        startingDirection = UP;
        break;
    }
    Graph testGraph("../maps/map_1.txt");
    GraphBFS testBFS(testGraph);
    printMaze(testGraph.maze);
    // start BFS
    pair<int, int> start = make_pair(startX, startY);
    pair<int, int> end = make_pair(endX, endY);
    if (!(testGraph.isValidCoords(start) && testGraph.isValidCoords(end))) {
        cerr << "invalid coordinates";
        throw exception();
    }
    testBFS.findShortestPath(start, end);
    vector<Movement> movements = findMovements(startingDirection, testGraph.maze, testBFS.shortestPath);
    exportPathToFile(testGraph, testBFS.shortestPath, movements, startingDirection);
    return 0;
}
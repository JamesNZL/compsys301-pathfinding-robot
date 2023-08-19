#include "../data structures/abstractTraversal.h"
#include "../data structures/graph.h"
#include "../utils/indexConversion.h"
#include "../utils/outputs.h"
#include "../utils/pathToTurns.h"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class ArrayDijkstras : AbstractTraversal {
public:
    ArrayDijkstras(Graph _graph) {
        graph = _graph;
    }
    void findShortestPath(pair<int, int> start, pair<int, int> end) override {
        int w = graph.mazeWidth;
        int h = graph.mazeHeight;
        vector<int> dY = {0, 0, -1, 1};
        vector<int> dX = {1, -1, 0, 0};

        vector<int> dist(w * h, INT32_MAX);
        vector<int> pred(w * h, -1);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        int start1D = pairTo1d(start, h, w);
        int end1D = pairTo1d(end, h, w);

        dist[start1D] = 0;
        pq.push({dist[start1D], start1D});

        while (!pq.empty()) {
            pair<int, int> current = pq.top();
            pq.pop();
            int currentDist = current.first;
            int currentNode = current.second;

            if (currentNode == end1D)
                break;

            pair<int, int> current2D = convertToXY(currentNode, h, w);

            for (int i = 0; i < 4; ++i) {
                int newX = current2D.first + dX[i];
                int newY = current2D.second + dY[i];
                if (newX >= 0 && newX < w && newY >= 0 && newY < h && graph.maze[newY][newX] == 0) {
                    int newDist = currentDist + 1;
                    int nextNode1D = pairTo1d({newX, newY}, h, w);
                    if (newDist < dist[nextNode1D]) {
                        dist[nextNode1D] = newDist;
                        pred[nextNode1D] = currentNode;
                        pq.push({newDist, nextNode1D});
                    }
                }
            }
        }

        // Build the path from end to start using the pred array
        stack<int> s;
        int currentCoords = end1D;
        while (currentCoords != start1D) {
            s.push(currentCoords);
            currentCoords = pred[currentCoords];
        }
        s.push(start1D); // Push the starting node

        shortestPath.clear(); // Clear any previous path
        while (!s.empty()) {
            pair<int, int> coord2d = convertToXY(s.top(), h, w);
            shortestPath.push_back(coord2d);
            s.pop();
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

    Graph testGraph("../maps/map_1.txt");
    ArrayDijkstras testDijkstras(testGraph);
    printMaze(testGraph.maze);
    // start Dijkstras
    pair<int, int> start = make_pair(startX, startY);
    pair<int, int> end = make_pair(endX, endY);
    if (!(testGraph.isValidCoords(start) && testGraph.isValidCoords(end))) {
        cerr << "invalid coordinates";
        throw exception();
    }
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
    testDijkstras.findShortestPath(start, end);
    vector<Movement> movements = findMovements(startingDirection, testGraph.maze, testDijkstras.shortestPath);
    exportPathToFile(testGraph, testDijkstras.shortestPath, movements, startingDirection);
    return 0;
}
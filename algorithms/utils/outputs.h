#ifndef OUTPUTS_H
#define OUTPUTS_H
#include "../data structures/graph.h"
#include "pathToTurns.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

void printMaze(vector<vector<int>> maze) {
    for (vector<int> row : maze) {
        for (int val : row) {
            cout << val;
        }
        cout << "\n";
    }
    cout << "\n";
}

void printShortestPath(vector<pair<int, int>> shortestPath) {
    for (pair<int, int> coords : shortestPath) {
        cout << "(" << coords.first << "," << coords.second << ")"
             << " ";
    }
    cout << "\n";
}
void printAdjList(unordered_map<int, vector<int>> adjList) {
    for (auto const &pair : adjList) {
        int key = pair.first;
        cout << key << ": ";
        vector<int> list = pair.second;
        for (int i : list) {
            cout << i << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void exportPathToFile(Graph graph, vector<pair<int, int>> shortestPath, vector<Movement> movements, Direction startingDirection) {
    vector<vector<int>> maze = graph.maze;
    stringstream pathString;
    for (pair<int, int> coords : shortestPath) {
        int x = coords.first;
        int y = coords.second;
        // use 2 to mark square as part of shortest path
        maze[y][x] = 2;
        // write nodes included in shortest path
        pathString << "(" << coords.first << "," << coords.second << ")"
                   << " ";
    }
    ofstream outFile("../visualisation/outputs/mazePath.txt");

    for (vector<int> list : maze) {
        for (int i : list) {
            outFile << i;
        }
        outFile << endl;
    }
    outFile << "==ENDMAZE" << endl;
    for (Movement movement : movements) {
        outFile << movementStrings[movement] << " ";
    }
    outFile << endl
            << "==ENDDIRS" << endl;
    outFile << directionStrings[startingDirection] << endl
            << "==ENDSTART" << endl;
    outFile << pathString.str();
    outFile.close();
}
#endif
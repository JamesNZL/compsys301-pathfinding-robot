#ifndef OUTPUTS_H
#define OUTPUTS_H
#include "../data structures/graph.h"
#include <iostream>
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
}

void exportPathToFile(Graph graph, vector<pair<int, int>> shortestPath) {
    vector<vector<int>> maze = graph.maze;
    for (pair<int, int> coords : shortestPath) {
        int x = coords.first;
        int y = coords.second;
        // use 2 to mark square as part of shortest path
        maze[y][x] = 2;
    }
    ofstream outFile("outputs/mazePath.txt");
    for (vector<int> list : maze) {
        for (int i : list) {
            outFile << i;
        }
        outFile << endl;
    }
    outFile.close();
}
#endif
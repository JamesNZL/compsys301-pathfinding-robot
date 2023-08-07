#ifndef PATHTOTURNS_H
#define PATHTOTURNS_H
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
#endif
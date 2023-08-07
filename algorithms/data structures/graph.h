#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../utils/indexConversion.h"
using namespace std;

class Graph {
public:
    Graph() {
    }
    Graph(string filepath) {
        createMaze(filepath);
        createAdjMatrix();
    }

    vector<vector<int>> maze;
    // TODO: every node has max 4 neighbours, possible optimization?
    unordered_map<int, vector<int>> adjList;
    int mazeWidth, mazeHeight;

private:
    void createAdjMatrix() {
        // add empty lists
        for (int i = 0; i < mazeWidth * mazeHeight; ++i) {
            adjList[i] = vector<int>{};
        }
        for (int y = 0; y < mazeHeight; ++y) {
            for (int x = 0; x < mazeWidth; ++x) {
                if (maze[y][x] == 1)
                    continue;
                checkAdjacent(x, y);
            }
        }
    }

    void checkAdjacent(int x, int y) {
        int dx[] = {-1, 1, 0, 0}; // Offsets for adjacent cells in x direction
        int dy[] = {0, 0, -1, 1}; // Offsets for adjacent cells in y direction
        int index1d = convertTo1d(x, y, mazeWidth);

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isInBounds(nx, ny) && maze[ny][nx] == 0)
                adjList[index1d].push_back(convertTo1d(nx, ny, mazeWidth));
        }
    }

    bool isInBounds(int x, int y) {
        bool horizontallyInBounds = x >= 0 && x < mazeWidth;
        bool verticallyInBounds = y >= 0 && y < mazeHeight;
        return horizontallyInBounds && verticallyInBounds;
    }
    void createMaze(string filepath) {
        ifstream inputFile(filepath);
        if (!inputFile) {
            cout << "failed to read file";
            return;
        }
        string line;
        // start from the first row
        while (getline(inputFile, line)) {
            vector<int> row;
            char currentChar;
            // assume the file only contains 1s and 0s
            for (char c : line) {
                if (c == '0') {
                    row.push_back(0);
                } else {
                    row.push_back(1);
                }
            }
            maze.push_back(row);
        }
        // store diemensions
        mazeHeight = maze.size();
        mazeWidth = maze[0].size();
    }
};

#endif // GRAPH_H

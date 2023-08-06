#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(string filepath) {
        createMatrix(filepath);
        printMaze();
    }

private:
    vector<vector<int>> maze;

    void printMaze() {
        for (vector<int> row : maze) {
            for (int val : row) {
                cout << val;
            }
            cout << "\n";
        }
    }

    void createMatrix(string filepath) {
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
    }
};

#endif // GRAPH_H

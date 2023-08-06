#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
using namespace std;

class Graph
{
public:
    Graph(string filepath)
    {
        createMatrix(filepath);
        printMaze();
    }

    void printMaze()
    {
        for (vector<int> row : maze)
        {
            for (int val : row)
            {
                cout << val;
            }
            cout << "\n";
        }
    }

private:
    vector<vector<int>> maze;

    void createMatrix(string filepath)
    {
        ifstream inputFile(filepath);
        if (!inputFile)
        {
            cout << "failed to read file";
            return;
        }
        string line;
        // start from first row
        while (getline(inputFile, line))
        {
            vector<int> row;
            char currentChar;
            // assume file only contains 1s and 0s
            for (char c : line)
            {
                if (c == '0')
                {
                    row.push_back(0);
                }
                else
                {
                    row.push_back(1);
                }
            }
            maze.push_back(row);
        }
    }
};

int main()
{
    Graph test("../map_1.txt");
    return 0;
}
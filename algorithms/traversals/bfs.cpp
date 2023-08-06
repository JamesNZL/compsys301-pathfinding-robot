#include "../data structures/graph.h"
#include <iostream>

using namespace std;

int main() {
    Graph test("../maps/map_1.txt");
    test.printMaze();
    test.printAdjList();
    return 0;
}
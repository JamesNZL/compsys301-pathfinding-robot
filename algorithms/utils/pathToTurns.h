#ifndef PATHTOTURNS_H
#define PATHTOTURNS_H
#include <vector>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Turn {
    LEFT,
    RIGHT
};

Direction getRelativeDirection(pair<int, int> current, pair<int, int> next) {
    int currentX = current.first;
    int currentY = current.second;
    int nextX = next.first;
    int nextY = next.second;

    // is in a different X position
    if (currentX != nextX) {
        // next is on the left
        if (nextX < currentX) {
            return Direction::LEFT;
        } else {
            return Direction::RIGHT;
        }
    } else {
        // y is different
        if (nextY < currentY) {
            // next is above
            return Direction::UP;
        } else {
            return Direction::DOWN;
        }
    }
}

Turn getRequiredTurn(Direction current, Direction next) {
}
void findDirections(vector<vector<int>> maze, vector<pair<int, int>> shortestPath) {
    // shortest path is already sorted
    for (pair<int, int> coords : shortestPath) {
        int x = coords.first;
        int y = coords.second;
    }
}

#endif
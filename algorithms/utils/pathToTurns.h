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

enum Movement {
    LEFT,
    RIGHT,
    STRAIGHT,
    AROUND
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

Movement getRequiredMovement(Direction current, Direction next) {
    switch (current) {
    case Direction::LEFT: {
        switch (next) {
        case Direction::LEFT:
            return Movement::STRAIGHT;
        case Direction::RIGHT:
            return Movement::AROUND;
        case Direction::UP:
            return Movement::RIGHT;
        case Direction::DOWN:
            return Movement::LEFT;
        }
    } break;
    case Direction::RIGHT: {
        switch (next) {
        case Direction::LEFT:
            return Movement::AROUND;
        case Direction::RIGHT:
            return Movement::STRAIGHT;
        case Direction::UP:
            return Movement::LEFT;
        case Direction::DOWN:
            return Movement::RIGHT;
        }
    } break;
    case Direction::UP: {
        switch (next) {
        case Direction::LEFT:
            return Movement::LEFT;
        case Direction::RIGHT:
            return Movement::RIGHT;
        case Direction::UP:
            return Movement::STRAIGHT;
        case Direction::DOWN:
            return Movement::AROUND;
        }
    } break;
    case Direction::DOWN: {
        switch (next) {
        case Direction::LEFT:
            return Movement::RIGHT;
        case Direction::RIGHT:
            return Movement::LEFT;
        case Direction::UP:
            return Movement::AROUND;
        case Direction::DOWN:
            return Movement::STRAIGHT;
        }
    } break;
    }
}
void findDirections(vector<vector<int>> maze, vector<pair<int, int>> shortestPath) {
    // shortest path is already sorted
    for (pair<int, int> coords : shortestPath) {
        int x = coords.first;
        int y = coords.second;
    }
}

#endif
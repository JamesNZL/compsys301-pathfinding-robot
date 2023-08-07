#ifndef PATHTOTURNS_H
#define PATHTOTURNS_H
#include <iostream>
#include <vector>

using namespace std;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum Movement {
    LEFT_,
    RIGHT_,
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
            return Movement::RIGHT_;
        case Direction::DOWN:
            return Movement::LEFT_;
        }
    } break;
    case Direction::RIGHT: {
        switch (next) {
        case Direction::LEFT:
            return Movement::AROUND;
        case Direction::RIGHT:
            return Movement::STRAIGHT;
        case Direction::UP:
            return Movement::LEFT_;
        case Direction::DOWN:
            return Movement::RIGHT_;
        }
    } break;
    case Direction::UP: {
        switch (next) {
        case Direction::LEFT:
            return Movement::LEFT_;
        case Direction::RIGHT:
            return Movement::RIGHT_;
        case Direction::UP:
            return Movement::STRAIGHT;
        case Direction::DOWN:
            return Movement::AROUND;
        }
    } break;
    case Direction::DOWN: {
        switch (next) {
        case Direction::LEFT:
            return Movement::RIGHT_;
        case Direction::RIGHT:
            return Movement::LEFT_;
        case Direction::UP:
            return Movement::AROUND;
        case Direction::DOWN:
            return Movement::STRAIGHT;
        }
    } break;
    }
}
vector<Movement> findMovements(Direction startingDirection, vector<vector<int>> maze, vector<pair<int, int>> shortestPath) {
    Direction currentDirection = startingDirection;
    vector<Movement> movements;

    // shortest path is already sorted
    for (int i = 0; i < shortestPath.size() - 1; ++i) {
        cout << currentDirection << " ";
        pair<int, int> coordsCurrent = shortestPath[i];
        pair<int, int> coordsNext = shortestPath[i + 1];
        Direction relativeDirection = getRelativeDirection(coordsCurrent, coordsNext);
        Movement movement = getRequiredMovement(currentDirection, relativeDirection);

        movements.push_back(movement);
        // we need to move after turning
        currentDirection = relativeDirection;
    }
    cout << "\n";
    return movements;
}

#endif
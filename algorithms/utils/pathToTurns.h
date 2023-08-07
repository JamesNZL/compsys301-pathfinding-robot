#ifndef PATHTOTURNS_H
#define PATHTOTURNS_H
#include <iostream>
#include <vector>

using namespace std;

vector<string> movementStrings = {"left", "right", "straight", "around", "skip"};
vector<string> directionStrings = {"up", "down", "left", "right"};
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
    AROUND,
    SKIP_TURN
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
    return Movement::SKIP_TURN;
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
        // we need to move after turning
        currentDirection = relativeDirection;
        // check if there are intersections
        int x = coordsCurrent.first;
        int y = coordsCurrent.second;
        if (movement == Movement::STRAIGHT) {
            switch (currentDirection) {
            case Direction::LEFT:
            case Direction::RIGHT:
                if (maze[y + 1][x] == 0 || maze[y - 1][x] == 0) {
                    movements.push_back(Movement::SKIP_TURN);
                }
                break;
            case Direction::UP:
            case Direction::DOWN:
                if (maze[y][x + 1] == 0 || maze[y][x - 1] == 0) {
                    movements.push_back(Movement::SKIP_TURN);
                }
                break;
            default:
                break;
            }
        } else {
            movements.push_back(movement);
        }
    }
    cout << "\n";
    return movements;
}

#endif
#ifndef INDEXCONVERSION_H
#define INDEXCONVERSION_H
#include <utility>
using namespace std;

// coords.first = x
// coords.second = y
pair<int, int> convertToXY(int index, int rows, int cols) {
    int row = index / cols;
    int col = index % cols;
    pair<int, int> coords2d;
    coords2d.first = col;
    coords2d.second = row;
    return coords2d;
}

int pairTo1d(pair<int, int> coords, int rows, int cols) {
    // x + y * max columns
    return coords.first + coords.second * cols;
}

int convertTo1d(int x, int y, int cols) {
    // x + y * max columns
    return x + y * cols;
}
#endif
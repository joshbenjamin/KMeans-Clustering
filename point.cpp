#include "point.h"
#include <iostream>

namespace BNJJOS003 {

    int index;
    int x;
    int y;
    int clusterNumber;

    point::point() {

    }

    point::~point() {
        index = 0;
        x = 0;
        y = 0;
        clusterNumber = 0;
    }

    void point::setX(int xVal) {
        x = xVal;
    }

    void point::setY(int yVal) {
        y = yVal;
    }

    void point::setIndex(int indVal) {
        index = indVal;
    }

    void point::setClusterNumber(int clus) {
        clusterNumber = clus;
    }

    void point::print() {
        std::cout << this->index << " " << this->x << " " << this->y << std::endl;
    }

};
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

    // Initialising methods

    void point::setX(int xVal) {
        x = xVal;
    }

    void point::setY(int yVal) {
        y = yVal;
    }

    void point::setIndex(int indVal) {
        index = indVal;
    }



    // Sets this current point's 'ownership' to one of the clusters
    void point::setClusterNumber(int clus) {
        clusterNumber = clus;
    }

    // This was just used for tracing
    void point::print() {
        std::cout << this->index << " " << this->x << " " << this->y << std::endl;
    }

};
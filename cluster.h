//
// Created by Joshua on 8/2/2018.
//

#ifndef INC_1_KMEANS_CLUSTER_H
#define INC_1_KMEANS_CLUSTER_H

#include "point.h"
#include <vector>
#include <string>
#include <fstream>

namespace BNJJOS003{

    class cluster{
    public:
        int number;
        double centroidX;
        double centroidY;
        std::vector <BNJJOS003::point> clusterPoints;

        cluster();
        cluster(int, double, double);
        ~cluster();

        void addPoint(BNJJOS003::point);
        void calculateNewCentroid();
        void changeCentroid(double, double);
        void emptyPoints();

        void writeToFile(std::ofstream &);
    };

}

#endif //INC_1_KMEANS_CLUSTER_H

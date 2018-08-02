#include "cluster.h"

namespace BNJJOS003{

    int index;
    double centroidX;
    double centroidY;
    std::vector <BNJJOS003::point> clusterPoints;

    cluster::cluster(int ind, double paramX, double paramY){
        index = ind;
        changeCentroid(paramX, paramY);
    }

    cluster::~cluster(){
        index = 0;
        centroidX = 0;
        centroidY = 0;
        clusterPoints.clear();
    }

    void cluster::addPoint(BNJJOS003::point p){
        clusterPoints.push_back(p);
    }

    void cluster::calculateNewCentroid() {
        double tempX = 0;
        double tempY = 0;

        for (auto &clusterPoint : clusterPoints) {
            tempX += clusterPoint.x;
            tempY += clusterPoint.y;
        }

        changeCentroid(tempX, tempY);
    }

    void cluster::changeCentroid(double x, double y){
        centroidX = x;
        centroidY = y;
    }

    void cluster::emptyPoints(){
        clusterPoints.clear();
    }

};


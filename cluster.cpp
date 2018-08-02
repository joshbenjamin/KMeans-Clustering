#include "cluster.h"
#include <iostream>
#include <string>

namespace BNJJOS003{

    int number;
    double centroidX;
    double centroidY;
    std::vector <BNJJOS003::point> clusterPoints;

    cluster::cluster() {

    }

    cluster::cluster(int ind, double paramX, double paramY){
        number = ind;
        changeCentroid(paramX, paramY);
    }

    cluster::~cluster(){
        number = 0;
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

        tempX = tempX/clusterPoints.size();
        tempY = tempY/clusterPoints.size();

        changeCentroid(tempX, tempY);
    }

    void cluster::changeCentroid(double x, double y){
        centroidX = x;
        centroidY = y;
    }

    void cluster::emptyPoints(){
        clusterPoints.clear();
    }

    /*
    std::string pointNames(){
        std::string pointsOutput = "";
        for (int i = 0; i < clusterPoints.size(); ++i) {
            pointsOutput = pointsOutput + std::to_string(clusterPoints[i].index) + ", ";
        }
        pointsOutput.substr(0, pointsOutput.length() - 2);

        return pointsOutput;
    }
    */

    void cluster::writeToFile(std::ofstream & output) {

        output << "Cluster " << number << ": ";

        if (clusterPoints.size() > 0) {
            for (int i = 0; i < clusterPoints.size() - 1; ++i) {
                output << clusterPoints[i].index << ", ";
            }
            output << clusterPoints[clusterPoints.size() - 1].index << std::endl;
        }
        else {
            output << std::endl;
        }
        output << "Centroid: (" << centroidX << ", " << centroidY << ")" << '\n' << std::endl;
    }

};


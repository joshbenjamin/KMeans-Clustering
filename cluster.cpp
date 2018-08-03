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

    // Creates the cluster with the supplied parameters for the centroid (As per the handout, Examples 1, 4 and 7)
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

    // Adds a point to this cluster if it is deemed the closest centroid to that point
    void cluster::addPoint(BNJJOS003::point p){
        clusterPoints.push_back(p);
    }

    // Takes the mean of the X and Y values from the points associated with this cluster
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

    // We set the centroid values with this method
    void cluster::changeCentroid(double x, double y){
        centroidX = x;
        centroidY = y;
    }

    // This is called at the end of each iteration as it doesn't matter where the points are,
    // their distance to each cluster centroid will still be calculated
    void cluster::emptyPoints(){
        clusterPoints.clear();
    }

    // Used to write the values of each cluster to the output fstream that is passed through as a paramter

    void cluster::writeToFile(std::ofstream & output) {

        output << "Cluster " << number << ": ";

        // Use this for loop to get the output of the points' index numbers to write to the file
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


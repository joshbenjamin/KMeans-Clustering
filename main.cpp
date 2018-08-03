#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "math.h"
#include "point.h"
#include "cluster.h"

using namespace std;

// Decided to use a class for the cluster instead of just a structure
/*struct Cluster {
    int number;
    vector<BNJJOS003::point> clusterPoints;
    vector<double, double> centroid;
};*/

// Calculates the Euclidean distance between 2 points and returns the value
double distance(int x1, double x2, int y1, double y2){
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

// Used for reading in points from the inout file given on the command line
vector<BNJJOS003::point> getPoints(string file, int k){

    string line;
    ifstream inputFile;
    inputFile.open(file);

    vector<BNJJOS003::point> tempPoints;

    // Takes the input file we have supplied and reads through all the points and creates them
    if(inputFile.is_open()){
        while (getline(inputFile, line)){
            istringstream iss(line);
            string temp;

            BNJJOS003::point p;

            int count = 0;
            while(getline(iss, temp, ' ')){

                // We use this to set the C, Y and index values, each separated by a single space in the file provided
                switch (count){

                    case 0:{
                        p.setIndex(atoi(temp.c_str()));
                    }break;

                    case 1:{
                        p.setX(atoi(temp.c_str()));
                    }break;

                    case 2:{
                        p.setY(atoi(temp.c_str()));
                    }break;

                }

                count++;

            }

            // This just assigns the points to a random cluster when they're created (Point 1 to Cluster 1 all the way to Point 4 to Cluster 1 and so on)
            p.setClusterNumber(((p.index-1)%k)+1);

            // Pushes the point into a vector we use temporarily
            tempPoints.push_back(p);

            // Just used for debugging
            //p.print();
        }

        inputFile.close();
    }
    else{
        cout << "No file found" << endl;
    }

    // Sends back the vector containing the points back to the place the method was called
    return tempPoints;
}

int main(int argc, const char * argv[]) {

    // Gets all of the values passed through as program parameter arguments
    int kElements = atoi(argv[1]);
    string inputFileName = argv[2];
    string outputFileName = argv[3];

    // Create the vector of points using the method we created
    vector<BNJJOS003::point> points = getPoints(inputFileName, kElements);

    vector <BNJJOS003::cluster> clusters;

    // This is basically the assigning of clusters to have the Centroids be the values of Examples 1, 4, 7.
    // I also just initialised the cluster here as well, seemed sensible
    for (int i = 1; i < points.size()+1; ++i) {
        if(i % kElements == 1){
            clusters.push_back(BNJJOS003::cluster((i/kElements+1), points[i-1].x, points[i-1].y));
        }
    }

    int iterations = 0;

    // This is used for the stopping statement so that we stop once the calculated centroid of all points in the space do not change
    std::vector<double> oldCentroidPoints;
    // Just have to make sure from the go that the 2 aren't the same, otherwise this is going to never run
    oldCentroidPoints.push_back(420);
    //oldCentroidPoints.push_back(69);
    std::vector<double> newCentroidPoints;

    ofstream outputFile(outputFileName);

    while (oldCentroidPoints != newCentroidPoints){

        iterations++;

        // We constantly change the new Centroid points, while the old ones become the new ones of yesteryear
        oldCentroidPoints = newCentroidPoints;
        newCentroidPoints.clear();

        for (int i = 0; i < clusters.size(); ++i) {
            clusters[i].emptyPoints();
        }



        for (int i = 0; i < points.size(); ++i) {

            // I use this to determine which cluster is closest to each point.
                    // I begin with the first cluster being the closest cluster and go along with that

            int newCluster = 0;
            double lowestDistance = distance(points[i].x, clusters[0].centroidX, points[i].y, clusters[0].centroidY);

            for (int j = 1; j < kElements; ++j) {

                // Here, if the new distance to the cluster is closer, we temporarily 'state' which one it is closest to
                double tempDist = distance(points[i].x, clusters[j].centroidX, points[i].y, clusters[j].centroidY);
                if (tempDist < lowestDistance){
                    lowestDistance = tempDist;
                    newCluster = j;
                }
            }

            // Here the point is assigned the cluster and the point is added to the cluster's vector of points associated with it
            points[i].setClusterNumber(newCluster+1);
            clusters[newCluster].addPoint(points[i]);

        }


        // Here, I make the change to the new centroid, so that the vector that we use for the stopping statement does not immediately equate to the previous one
        for (int i = 0; i < clusters.size(); ++i) {

            clusters[i].calculateNewCentroid();
            newCentroidPoints.push_back(clusters[i].centroidX);
            newCentroidPoints.push_back(clusters[i].centroidY);

        }

        outputFile << "Iteration " << iterations << '\n' << endl;

        for (int i = 0; i < clusters.size(); ++i) {
            clusters[i].writeToFile(outputFile);
        }

    }

    outputFile.close();

    return 0;
}
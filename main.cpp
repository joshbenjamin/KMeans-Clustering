#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "math.h"
#include "point.h"
#include "cluster.h"

using namespace std;

/*struct Cluster {
    int number;
    vector<BNJJOS003::point> clusterPoints;
    vector<double, double> centroid;
};*/

double distance(int x1, double x2, int y1, double y2){
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

vector<BNJJOS003::point> getPoints(string file, int k){

    string line;
    ifstream inputFile;
    inputFile.open(file);

    vector<BNJJOS003::point> tempPoints;

    if(inputFile.is_open()){
        while (getline(inputFile, line)){
            //cout << line << endl;
            istringstream iss(line);
            string temp;

            BNJJOS003::point p;

            int count = 0;
            while(getline(iss, temp, ' ')){

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

            p.setClusterNumber(((p.index-1)%k)+1);

            tempPoints.push_back(p);
            p.print();
        }

        inputFile.close();
    }
    else{
        cout << "No file found" << endl;
    }

    return tempPoints;
}

int main(int argc, const char * argv[]) {

    int kElements = atoi(argv[1]);
    string input = argv[2];

    vector<BNJJOS003::point> points = getPoints(input, kElements);

    vector <BNJJOS003::cluster> clusters;

    for (int i = 1; i < points.size()+1; ++i) {
        if(i % kElements == 1){
            clusters.push_back(BNJJOS003::cluster((i/kElements+1), points[i-1].x, points[i-1].y));
        }
    }

    int iterations = 0;

    while (iterations < 11){

        iterations++;

        for (int i = 0; i < clusters.size(); ++i) {
            clusters[i].emptyPoints();
        }



        for (int i = 0; i < points.size(); ++i) {

            int newCluster = 0;
            double lowestDistance = distance(points[i].x, clusters[0].centroidX, points[i].y, clusters[0].centroidY);

            for (int j = 1; j < kElements; ++j) {

                double tempDist = distance(points[i].x, clusters[j].centroidX, points[i].y, clusters[j].centroidY);
                if (tempDist < lowestDistance){
                    lowestDistance = tempDist;
                    newCluster = j;
                }
            }

            points[i].setClusterNumber(newCluster+1);
            clusters[newCluster].addPoint(points[i]);

        }



        for (int i = 0; i < clusters.size(); ++i) {

            clusters[i].calculateNewCentroid();

        }



        cout << "Iteration " << iterations << '\n' << endl;

        for (int i = 0; i < clusters.size(); ++i) {
            clusters[i].print();
        }

    }

    return 0;
}
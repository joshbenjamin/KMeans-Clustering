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
    int index;
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

            p.setClusterNumber(p.index%k);

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
            clusters.push_back(BNJJOS003::cluster(int((i/kElements)+1), points[i-1].x, points[i].y));
        }
    }

    while (newPoints != oldPoints){

        for (int i = 0; i < points.size(); ++i) {
            //double dist = 10;
            int centIndex = 0;

            for (int j = 0; j < kElements; ++j) {
                double tempDist = distance(points[i].x, clusters[j].x, points[j].y, clusters[j].y);
                if (tempDist < dist){

                }
            }

        }

    }

    return 0;
}
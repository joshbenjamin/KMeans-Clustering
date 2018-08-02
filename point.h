//
// Created by Joshua on 7/27/2018.
//

#ifndef INC_1_KMEANS_POINT_H
#define INC_1_KMEANS_POINT_H

namespace BNJJOS003 {

    class point {

        public:
            int index;
            int x;
            int y;
            int clusterNumber;

            point();
            ~point();

            void setX(int);
            void setY(int);
            void setIndex(int);
            void setClusterNumber(int);

            void print();

    };

}

#endif //INC_1_KMEANS_POINT_H

//
// Created by agla on 2021-06-22.
//

#ifndef FREIGHT_FREIGHT_PATH_H
#define FREIGHT_FREIGHT_PATH_H
#include <string>
#include <iostream>
using namespace std;



class Freight_Path {
private:
    int mission_id;
    float **$distance_matrix;

public:
    Freight_Path(int missionId);
    string find_route();

    string get_points();
};


#endif //FREIGHT_FREIGHT_PATH_H

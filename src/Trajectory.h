#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <vector>
#include "Model.h"
#include "config.h"
using namespace std;

class Trajectory
{
public:
    Trajectory();
    void clearTraj();
    void plan(CGeoPoint start, CGeoPoint end, vector<Obstacle> obs);
    void setTrajectoryMethod(int method);
    vector<CGeoPoint> trajVec;
private:
    int trajMethod;
};


#endif // ALGORITHM_H

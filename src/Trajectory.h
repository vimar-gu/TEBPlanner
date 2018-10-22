#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <vector>
#include "Model.h"
#include "config.h"
using namespace std;

namespace {
    const int RRT = 0;
    const int TEB = 1;
}

class Trajectory
{
public:
    Trajectory();
    void clearTraj();
    void plan(CGeoPoint start, CGeoPoint end, vector<Obstacle> obs);
    void setTrajectoryMethod(int method);
    State* getFirstState();
    vector<State*> trajVec;
private:
    int trajMethod;
};


#endif // ALGORITHM_H

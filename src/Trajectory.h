#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <vector>
#include "Model.h"
#include "config.h"
#include <time.h>
using namespace std;

namespace {
    const int RRT = 0;
    const int TEB = 1;
}

class Trajectory
{
public:
    Trajectory() {}
    ~Trajectory() {}
    void clearTraj();
    void plan(State start, State end, vector<Obstacle> obs);
    void setTrajectoryMethod(int method);
    void makeRRT2Line(vector<CGeoPoint>& rrtTrajVec, CGeoPoint start);
    vector<State*> trajVec;

private:
    int trajMethod;
};

#endif // ALGORITHM_H

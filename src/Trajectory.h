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
    Trajectory() : start_(CGeoPoint(-999, -999)), end_(CGeoPoint(-999, -999)) {}
    ~Trajectory() {}
    void clearTraj();
    void plan(State start, State end, vector<Obstacle> obs);
    bool checkUpdate(State start, State end, vector<Obstacle>& obs);
    void setTrajectoryMethod(int method);
    void makeRRT2Line(vector<CGeoPoint>& rrtTrajVec);
    vector<CGeoPoint> rrtTrajVec;
    vector<State*> trajVec;

private:
    int trajMethod;
    State start_;
    State end_;
    int nextState;
};

#endif // ALGORITHM_H

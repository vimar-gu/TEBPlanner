#ifndef TEBPLANNER_H
#define TEBPLANNER_H
#include "Model.h"
#include "config.h"
#include <iostream>
using namespace std;

class TEBPlanner
{
public:
    TEBPlanner() {}
    TEBPlanner(vector<State*>& trajVec, State start, State end, vector<Obstacle> obs) :
        trajVec_(trajVec), start_(start), end_(end), obs_(obs){}
    void plan();
    void initOptimize();
    void optimizeState();
    void clear();
    pair<Obstacle, Obstacle> getMainObstacle(State* current);
private:
    vector<State*> trajVec_;
    vector<Obstacle> obs_;
    State start_;
    State end_;
};

#endif // TEBPLANNER_H

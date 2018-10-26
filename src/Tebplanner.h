#ifndef TEBPLANNER_H
#define TEBPLANNER_H
#include "Model.h"
#include "config.h"
#include "Optimizer.h"
#include <iostream>
using namespace std;

class TEBPlanner
{
public:
//    TEBPlanner() {}
    TEBPlanner(vector<State*>& trajVec, State start, State end, vector<Obstacle> obs) :
        start_(start), end_(end), obs_(obs) { plan(trajVec); }
    void plan(vector<State*>& trajVec);
    void initOptimize();

    void addVelocityForce(State* frontState, State* currentState);
    void addVelocityEndForce(State* currentState, State* endState);
    void addAccelerationForce(State* frontState, State* currentState, State* backState);
    void addAccelerationStartForce(State* currentState);
    void addAccelerationEndForce(State *currentState);
    void addObstacleForce(State* obstacleState, State* currentState);
    void prune(vector<State*>& trajVec);

    pair<Obstacle, Obstacle> getMainObstacle(State* current);
private:
    Optimizer optim_;
    vector<Obstacle> obs_;
    State start_;
    State end_;
};

#endif // TEBPLANNER_H

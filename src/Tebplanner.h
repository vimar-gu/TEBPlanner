#ifndef TEBPLANNER_H
#define TEBPLANNER_H
#include "Model.h"
#include "config.h"
#include <iostream>
using namespace std;


class TEBPlanner
{
public:
    TEBPlanner();
    TEBPlanner(vector<State>& trajVec, CGeoPoint start, CGeoPoint end, vector<Obstacle> obs);
    void plan(vector<State>& trajVec, CGeoPoint start, CGeoPoint end);
    pair<Obstacle, Obstacle> getMainObstacle(State current);
    CVector calcFrontForce(State front, State current);
    CVector calcBackForce(State current, State back);
    CVector calcObstacleForce(State current, Obstacle obs);
private:
    vector<Obstacle> obs_;
};

#endif // TEBPLANNER_H

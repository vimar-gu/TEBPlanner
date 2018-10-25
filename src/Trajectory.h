#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <iostream>
#include <vector>
#include "Model.h"
#include "config.h"
#include "rrtTree.h"
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
    bool generateRandNode(rrtTree::rrtNode& q_rand);
    void clearTraj();
    void setStart(const CGeoPoint& s);
    void setGoal(const CGeoPoint& g);
    void setNearestNode(const CGeoPoint& p);
    rrtTree::rrtNode getStart();
    rrtTree::rrtNode getGoal();
    void findPath(const CGeoPoint& s, const CGeoPoint& g, vector<Obstacle> obs);
    bool addNewNode2RRT(rrtTree::rrtNode& q_rand);
    bool checkNode2Goal(rrtTree::rrtNode& node);
    bool checkCollision(const CGeoPoint& p);
    bool pointCheck(rrtTree::rrtNode& m, rrtTree::rrtNode& n);
    void setTrajectoryMethod(int method);
    void plan(CGeoPoint start, CGeoPoint end, vector<Obstacle> obs);
    vector<int> getPath(int end_id);
    vector<State> trajVec;

private:
    int trajMethod;
    rrtTree my_rrt;
    vector<Obstacle> obs;
    rrtTree::rrtNode start, goal, nearest_goal;
    double distance_to_goal;
};

#endif // ALGORITHM_H

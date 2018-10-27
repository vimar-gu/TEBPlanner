#include "Trajectory.h"
#include "TEBPlanner.h"
#include "RRTPlanner.h"

using namespace std;

void Trajectory::clearTraj() {
    vector<State*>().swap(trajVec);
}

void Trajectory::plan(State start, State end, vector<Obstacle> obs) {
    clearTraj();
    RRTPlanner rrtPlanner(start.pos(), end.pos(), obs);
    bool pathUpdated = rrtPlanner.findRRTPath(trajVec);
//    TEBPlanner tebPlanner(trajVec, start, end, obs);
}

void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}




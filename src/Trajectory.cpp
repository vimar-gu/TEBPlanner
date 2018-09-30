#include "Trajectory.h"
#include "Tebplanner.h"

Trajectory::Trajectory() {

}

void Trajectory::clearTraj() {
    vector<State>().swap(trajVec);
}

void Trajectory::plan(CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    clearTraj();
    CVector start2End = end - start;
    CVector length = start2End / (TRAJ_POINT_NUMBER + 1);
    for (int i = 1; i <= TRAJ_POINT_NUMBER; i++) {
        State tempState(start + length * i);
        trajVec.push_back(tempState);
    }
    TEBPlanner tebPlanner(trajVec, start, end, obs);
}

void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}

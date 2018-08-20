#include "Trajectory.h"

Trajectory::Trajectory()
{

}

void Trajectory::clearTraj() {
    vector<CGeoPoint>().swap(trajVec);
}

void Trajectory::plan(CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    clearTraj();
    CVector start2End = end - start;
    CVector length = start2End / TRAJ_POINT_NUMBER;
    for (int i = 0; i < TRAJ_POINT_NUMBER; i++) {
        trajVec.push_back(start + length * i);
    }
}

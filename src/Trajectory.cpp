#include "Trajectory.h"

Trajectory::Trajectory() {

}

void Trajectory::clearTraj() {
    vector<State*>().swap(trajVec);
}

void Trajectory::plan(State start, State end, vector<Obstacle> obs) {
    clearTraj();
    CVector start2End = end.pos() - start.pos();
    CVector length = start2End / (TRAJ_POINT_NUMBER + 1);
    for (int i = 1; i <= TRAJ_POINT_NUMBER; i++) {
        State* tempState = new State(start.pos() + length * i);
        trajVec.push_back(tempState);
    }
}

State* Trajectory::getFirstState() {
    return trajVec[0];
}

void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}

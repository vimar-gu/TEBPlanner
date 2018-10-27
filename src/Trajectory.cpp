#include "Trajectory.h"
#include "TEBPlanner.h"
#include "RRTPlanner.h"

using namespace std;

void Trajectory::clearTraj() {
    vector<State*>().swap(trajVec);
}

void Trajectory::plan(State start, State end, vector<Obstacle> obs) {
    clearTraj();
    vector<CGeoPoint> rrtTrajVec;
    RRTPlanner rrtPlanner(start.pos(), end.pos(), obs);
    bool pathUpdated = rrtPlanner.findRRTPath(rrtTrajVec);
    if (pathUpdated) {
        makeRRT2Line(rrtTrajVec, start.pos());
    }
//    TEBPlanner tebPlanner(trajVec, start, end, obs);
}

void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}

void Trajectory::makeRRT2Line(vector<CGeoPoint>& rrtTrajVec, CGeoPoint start) {
    double routeLength = 0;
    for (size_t i = 0; i < rrtTrajVec.size() - 1; i++) {
        routeLength += (rrtTrajVec[i] - rrtTrajVec[i + 1]).mod();
    }
    for (size_t i = 0; i < rrtTrajVec.size() - 1; i++){
        CVector tempVec = (rrtTrajVec[i + 1] - rrtTrajVec[i]);
        int trajNum = tempVec.mod() / routeLength * TRAJ_POINT_NUMBER;
        for (int j = 0; j < trajNum; j++) {
            State* tempState = new State(rrtTrajVec[i] + tempVec / trajNum * (j + 1));
            trajVec.push_back(tempState);
        }
    }
}

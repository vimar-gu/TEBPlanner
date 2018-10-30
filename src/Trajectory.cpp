#include "Trajectory.h"
#include "TEBPlanner.h"
#include "RRTPlanner.h"

using namespace std;

void Trajectory::clearTraj() {
    vector<State*>().swap(trajVec);
}

void Trajectory::plan(State start, State end, vector<Obstacle> obs) {
    clearTraj();
    bool needUpdate = checkUpdate(start, end, obs);

    if (needUpdate) {
        start_ = start;
        RRTPlanner rrtPlanner(start.pos(), end.pos(), obs);
        bool pathUpdated = rrtPlanner.findRRTPath(rrtTrajVec);
        if (pathUpdated) {
            makeRRT2Line(rrtTrajVec);
        }
    }
    TEBPlanner tebPlanner(trajVec, start, end, obs);
}

bool Trajectory::checkUpdate(State start, State end, vector<Obstacle>& obs) {

    // the traj is not initiated
    if (trajVec.size() == 0 || rrtTrajVec.size() == 0 || rrtTrajVec.size() == 1)
        return true;

    // the target is changed
    if (!(end_ == end)) {
        end_ = end;
        return true;
    }

    // the current place is not on the trajectory
    nextState = trajVec[0];
    CGeoSegment tmpSeg(start_.pos(), nextState->pos());
    double minDist2Traj = tmpSeg.dist2Point(start.pos());
    size_t i = 1;
    for (; i < trajVec.size(); i++) {
        tmpSeg = CGeoSegment(trajVec[i - 1]->pos(), trajVec[i]->pos());
        if (tmpSeg.dist2Point(start.pos()) < minDist2Traj) {
            minDist2Traj = tmpSeg.dist2Point(start.pos());
            nextState = trajVec[i];
        }
    }
    if (minDist2Traj > 5) return true;

//    for (int i = 0; i < rrtTrajVec.size(); i++) qDebug() << i << rrtTrajVec[i].x() << rrtTrajVec[i].y();
    for (size_t i = 0; i < obs.size(); i++) {
        if (obs[i].checkSegment(start.pos(), rrtTrajVec[1])) {
            return true;
        }
    }

    return false;
}

void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}

void Trajectory::makeRRT2Line(vector<CGeoPoint>& rrtTrajVec) {
    clearTraj();
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

#include "Tebplanner.h"

TEBPlanner::TEBPlanner() {

}

TEBPlanner::TEBPlanner(vector<State> &trajVec, CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    obs_ = obs;
    plan(trajVec, start, end);
}

void TEBPlanner::plan(vector<State> &trajVec, CGeoPoint start, CGeoPoint end) {
    int index = 0;
    while (index < MAX_ITERATION_TIMES) {

        // init

        CVector totalLoss = CVector(0, 0);
        CVector frontLoss, backLoss, leftObstacleLoss, rightObstacleLoss;

        // deal with boundary conditions

        if (trajVec.empty()) return;
        else if (trajVec.size() == 1) {

        }

        // calc the loss for every traj state

        for (int i = 0; i < trajVec.size(); i++) {

            // decide the main obstacle for this traj state

            pair<Obstacle> obs = getMainObstacle(trajVec[i]);

            // calc losses

            if (i == 0) { // the first point
                frontLoss = calcFrontForce(start, trajVec[i]);
                backLoss = calcBackForce(trajVec[i], trajVec[i + 1]);
            }
            else if (i == trajVec.size() - 1) { // the final point
                frontLoss = calcFrontForce(trajVec[i - 1], trajVec[i]);
                backLoss = calcBackForce(trajVec[i], end);
            }
            else { // normal points
                frontLoss = calcFrontForce(trajVec[i - 1], trajVec[i]);
                backLoss = calcBackForce(trajVec[i], trajVec[i + 1]);
            }
            leftObstacleLoss = calcObstacleForce(trajVec[i], obs.first);
            rightObstacleLoss = calcObstacleForce(trajVec[i], obs.second);

            // make decisions based on different conditions

            totalLoss += frontLoss + backLoss + leftObstacleLoss + rightObstacleLoss;
            totalLossMod = totalLoss.mod();
        }
    }
}

pair<Obstacle> TEBPlanner::getMainObstacle(State current) {

}

CVector TEBPlanner::calcFrontForce(State front, State current) {
    return CVector(0, 0);
}

CVector TEBPlanner::calcBackForce(State current, State back) {
    return CVector(0, 0);
}

CVector TEBPlanner::calcObstacleForce(State current, Obstacle obs) {
    return CVector(0, 0);
}

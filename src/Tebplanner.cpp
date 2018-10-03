#include "Tebplanner.h"
#include "Utils.h"
#include <QDebug>

TEBPlanner::TEBPlanner() {

}

TEBPlanner::TEBPlanner(vector<State> &trajVec, CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    obs_ = obs;
    plan(trajVec, start, end);
}

void TEBPlanner::plan(vector<State> &trajVec, CGeoPoint start, CGeoPoint end) {
    int index = 0;
    while (index < MAX_ITERATION_TIMES) {
        index++;

        // init

        CVector totalLoss = CVector(0, 0);
        double totalLossMod = 0;
        CVector frontLoss, backLoss, leftObstacleLoss, rightObstacleLoss;

        // deal with boundary conditions

        if (trajVec.empty()) return;
        else if (trajVec.size() == 1) {
            pair<Obstacle, Obstacle> obs = getMainObstacle(trajVec[0]);
            leftObstacleLoss = calcObstacleForce(trajVec[0], obs.first);
            rightObstacleLoss = calcObstacleForce(trajVec[0], obs.second);
            totalLoss = leftObstacleLoss + rightObstacleLoss;
            return;
        }

        // calc the loss for every traj state

        for (int i = 0; i < trajVec.size(); i++) {

            // decide the main obstacle for this traj state

            pair<Obstacle, Obstacle> obs = getMainObstacle(trajVec[i]);

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

            totalLoss = frontLoss + backLoss + leftObstacleLoss + rightObstacleLoss;
            totalLossMod = totalLoss.mod();

            if (totalLossMod > 1) {
                double changeMod = 10 / (1 + exp(-totalLossMod));
                double changeDir = totalLoss.dir();
                trajVec[i].setPos(trajVec[i].pos() + polar2Vector(changeMod, changeDir));
            }
        }
    }
}

pair<Obstacle, Obstacle> TEBPlanner::getMainObstacle(State current) {
    Obstacle leftObs, rightObs;
    double leftObsDist = MIN_OBSTACLE_DISTANCE, rightObsDist = MIN_OBSTACLE_DISTANCE;
    bool leftObsFlag = false, rightObsFlag = false;
    for (Obstacle obs : obs_) {
        if (normalize(current.dir() - (obs.pos() - current.pos()).dir()) > 0) { // obstacle is on the left
            if ((obs.pos() - current.pos()).mod() < leftObsDist) {
                leftObs = obs;
                leftObsFlag = true;
                leftObsDist = (obs.pos() - current.pos()).mod();
            }
        }
        else { // obstacle is on the right
            if ((obs.pos() - current.pos()).mod() < rightObsDist) {
                rightObs = obs;
                rightObsFlag = true;
                rightObsDist = (obs.pos() - current.pos()).mod();
            }
        }
    }
    pair<Obstacle, Obstacle> mainObstacle(Obstacle(-9999, -9999), Obstacle(-9999, -9999));
    if (leftObsFlag) mainObstacle.first = leftObs;
    if (rightObsFlag) mainObstacle.second = rightObs;
    return mainObstacle;
}

CVector TEBPlanner::calcFrontForce(State front, State current) {
    return CVector(0, 0);
}

CVector TEBPlanner::calcBackForce(State current, State back) {
    return CVector(0, 0);
}

CVector TEBPlanner::calcObstacleForce(State current, Obstacle obs) {
    if (obs.pos() == CGeoPoint(-9999, -9999)) return CVector(0, 0);
    else {
        double forceMod = 100 / exp((current.pos() - obs.pos()).mod() - 2 * OBSTACLE_RADIUS);
        double forceDir = (current.pos() - obs.pos()).dir();
        return polar2Vector(forceMod, forceDir);
    }
}

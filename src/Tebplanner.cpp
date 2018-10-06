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
        CVector velocityLoss, accelerationLoss, leftObstacleLoss, rightObstacleLoss;

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

        for (int i = 0; i < trajVec.size() - 1; i++) {

            // decide the main obstacle for this traj state

            pair<Obstacle, Obstacle> obs = getMainObstacle(trajVec[i]);

            // calc losses

            if (i == 0) { // the first point
                velocityLoss = calcVelocityForce(start, trajVec[i]);
                accelerationLoss = calcAccelerationStartForce(start, trajVec[i]);
            }
            else if (i == trajVec.size() - 1) { // the final point
                velocityLoss = calcVelocityEndForce(trajVec[i], end);
                accelerationLoss = calcAccelerationEndForce(trajVec[i], end);
            }
            else { // normal points
                velocityLoss = calcVelocityForce(trajVec[i - 1], trajVec[i]);
                accelerationLoss = calcAccelerationForce(trajVec[i - 1], trajVec[i], trajVec[i + 1]);
            }
            leftObstacleLoss = calcObstacleForce(trajVec[i], obs.first);
            rightObstacleLoss = calcObstacleForce(trajVec[i], obs.second);

            // make decisions based on different conditions

            qDebug() << velocityLoss.mod() << accelerationLoss.mod() << leftObstacleLoss.mod() << rightObstacleLoss.mod();
            totalLoss = velocityLoss + accelerationLoss + leftObstacleLoss + rightObstacleLoss;
            totalLossMod = totalLoss.mod();

            if (totalLossMod > 1) {
                double changeMod = 10 * tanh(totalLossMod / 100);
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

CVector TEBPlanner::calcVelocityForce(State front, State current) {
    CVector currentVel = (current.pos() - front.pos()) * FRAME_NUMBER;
    double forceMod = currentVel.mod() - MAX_VELOCITY;
    double forceDir = forceMod > 0 ? (front.pos() - current.pos()).dir() : (current.pos() - front.pos()).dir();
    return polar2Vector(fabs(forceMod) / 10, forceDir);
}

CVector TEBPlanner::calcVelocityEndForce(State current, State end) {
    return CVector(0, 0);
}

CVector TEBPlanner::calcAccelerationForce(State front, State current, State next) {
    CVector frontVel = (current.pos() - front.pos()) * FRAME_NUMBER;
    CVector nextVel = (next.pos() - current.pos()) * FRAME_NUMBER;
    CVector currentAcc = (nextVel - frontVel) * FRAME_NUMBER;
    double forceMod = currentAcc.mod() > MAX_ACCELERATION ? currentAcc.mod() - MAX_ACCELERATION : 0;
    double forceDir = (front.pos() - current.pos()).dir();
    return polar2Vector(fabs(forceMod) / 1000, forceDir);
}

CVector TEBPlanner::calcAccelerationStartForce(State start, State current) {
    CVector frontVel = start.vel();
    CVector nextVel = (current.pos() - start.pos()) * FRAME_NUMBER;
    CVector currentAcc = (nextVel - frontVel) * FRAME_NUMBER;
    double forceMod = currentAcc.mod() > MAX_ACCELERATION ? currentAcc.mod() - MAX_ACCELERATION : 0;
    double forceDir = (start.pos() - current.pos()).dir();
    return polar2Vector(fabs(forceMod) / 1000, forceDir);
}

CVector TEBPlanner::calcAccelerationEndForce(State current, State end) {
    return CVector(0, 0);
}

CVector TEBPlanner::calcObstacleForce(State current, Obstacle obs) {
    if (obs.pos() == CGeoPoint(-9999, -9999)) return CVector(0, 0);
    else {
        double forceMod = (current.pos() - obs.pos()).mod() >= MIN_OBSTACLE_DISTANCE ? 0 : MIN_OBSTACLE_DISTANCE - (current.pos() - obs.pos()).mod();
        double forceDir = (current.pos() - obs.pos()).dir();
        return polar2Vector(forceMod, forceDir);
    }
}

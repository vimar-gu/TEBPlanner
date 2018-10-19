#include "Tebplanner.h"
#include "Utils.h"
#include <QDebug>


void TEBPlanner::plan(vector<State*>& trajVec) {

    // initiate

    initOptimize();
    int index = 0;

    while (index < OUTER_ITERATION_TIMES) {
        index++;

        // boundary conditions

        if (trajVec.size() == 0) return;

        for (size_t i = 0; i < trajVec.size(); i++) {

            optim_.init();

            pair<Obstacle, Obstacle> mainObstacles = getMainObstacle(trajVec[i]);
            Obstacle leftObstacle = mainObstacles.first;
            Obstacle rightObstacle = mainObstacles.second;

            // start of the trajectory vector

            if (i == 0) {
//                prune(trajVec);

                addVelocityForce(&start_, trajVec[i]);
                addAccelerationStartForce(trajVec[i]);
                addObstacleForce(&leftObstacle, trajVec[i]);
                addObstacleForce(&rightObstacle, trajVec[i]);
            }

            // end of the trajectory vector

            else if (i == trajVec.size() - 1) {
                addVelocityEndForce(trajVec[i - 1], trajVec[i]);
                addAccelerationEndForce(trajVec[i]);
                addObstacleForce(&leftObstacle, trajVec[i]);
                addObstacleForce(&rightObstacle, trajVec[i]);
            }

            // default condition

            else {
                addVelocityForce(trajVec[i - 1], trajVec[i]);
                addAccelerationForce(trajVec[i - 1], trajVec[i], trajVec[i + 1]);
                addObstacleForce(&leftObstacle, trajVec[i]);
                addObstacleForce(&rightObstacle, trajVec[i]);
            }

            // do the optimization
//            if (i == 0) {
                optim_.optimize(INNER_ITERATION_TIMES, trajVec, i);
//            }
            optim_.clear();
        }
    }
}

void TEBPlanner::initOptimize() {

}

void TEBPlanner::addVelocityForce(State *frontState, State *currentState) {
    VelocityForce* force = new VelocityForce();
    force->setParam(0, frontState);
    force->setParam(1, currentState);
    optim_.addForce(force);
}

void TEBPlanner::addVelocityEndForce(State *currentState, State *endState) {
    VelocityForce* force = new VelocityForce();
    force->setParam(0, currentState);
    force->setParam(1, endState);
    optim_.addForce(force);
}

void TEBPlanner::addAccelerationForce(State *frontState, State *currentState, State *backState) {
    AccelerationForce* force = new AccelerationForce();
    force->setParam(0, frontState);
    force->setParam(1, currentState);
    force->setParam(2, backState);
    optim_.addForce(force);
}

void TEBPlanner::addAccelerationStartForce(State *currentState) {
    AccelerationStartForce* force = new AccelerationStartForce();
    force->setParam(0, &start_);
    force->setParam(1, currentState);
    optim_.addForce(force);
}

void TEBPlanner::addAccelerationEndForce(State *currentState) {
    AccelerationEndForce* force = new AccelerationEndForce();
    force->setParam(0, currentState);
    force->setParam(1, &end_);
    optim_.addForce(force);
}

void TEBPlanner::addObstacleForce(State *obstacleState, State *currentState) {
    ObstacleForce* force = new ObstacleForce();
    force->setParam(0, obstacleState);
    force->setParam(1, currentState);
    optim_.addForce(force);
}


void TEBPlanner::prune(vector<State*>& trajVec) {
    int len = trajVec.size() - 1;
    addVelocityEndForce(trajVec[len - 1], trajVec[len]);
    addAccelerationEndForce(trajVec[len]);
    CVector totalForce = optim_.calcTotalForce();

    if (totalForce.mod() > MAX_END_FORCE) { // need to add more trajectory points
        State* finalState = trajVec[len];
        State* tempState = new State((finalState->pos().x() + end_.pos().x()) / 2, (finalState->pos().y() + end_.pos().y()) / 2);
        trajVec.push_back(tempState);
    }

    optim_.clear();
}


pair<Obstacle, Obstacle> TEBPlanner::getMainObstacle(State* current) {
    Obstacle leftObs, rightObs;
    double leftObsDist = MIN_OBSTACLE_DISTANCE, rightObsDist = MIN_OBSTACLE_DISTANCE;
    bool leftObsFlag = false, rightObsFlag = false;
    for (Obstacle obs : obs_) {
        if (normalize(current->dir() - (obs.pos() - current->pos()).dir()) > 0) { // obstacle is on the left
            if ((obs.pos() - current->pos()).mod() < leftObsDist) {
                leftObs = obs;
                leftObsFlag = true;
                leftObsDist = (obs.pos() - current->pos()).mod();
            }
        }
        else { // obstacle is on the right
            if ((obs.pos() - current->pos()).mod() < rightObsDist) {
                rightObs = obs;
                rightObsFlag = true;
                rightObsDist = (obs.pos() - current->pos()).mod();
            }
        }
    }
    pair<Obstacle, Obstacle> mainObstacle;
    if (leftObsFlag) mainObstacle.first = leftObs;
    if (rightObsFlag) mainObstacle.second = rightObs;
    return mainObstacle;
}

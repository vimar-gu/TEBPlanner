#include "Tebplanner.h"
#include "Utils.h"
#include <QDebug>


void TEBPlanner::plan() {

    // initiate

    initOptimize();
    int index = 0;

    while (index < OUTER_ITERATION_TIMES) {
        index++;

        // boundary conditions

        if (trajVec_.size() == 0) return;

        for (int i = 0; i < trajVec_.size(); i++) {

            optim_.init();

            pair<Obstacle, Obstacle> mainObstacles = getMainObstacle(trajVec_[i]);
            Obstacle* leftObstacle = &mainObstacles.first;
            Obstacle* rightObstacle = &mainObstacles.second;

            // start of the trajectory vector

            if (i == 0) {

            }

            // end of the trajectory vector

            else if (i == trajVec_.size() - 1) {

            }

            // default condition

            else {
                addVelocityForce(trajVec_[i - 1], trajVec_[i]);
                addAccelerationForce(trajVec_[i - 1], trajVec_[i], trajVec_[i + 1]);
                addObstacleForce(leftObstacle, trajVec_[i]);
                addObstacleForce(rightObstacle, trajVec_[i]);
            }

            // do the optimization

            optim_.optimize(INNER_ITERATION_TIMES);
            optim_.clear();
        }
    }
}

void TEBPlanner::initOptimize() {

}

void TEBPlanner::addVelocityForce(State *frontState, State *currentState) {
    VelocityForce force;
    force.setParam(0, frontState);
    force.setParam(1, currentState);
    optim_.addForce(force);
}

void TEBPlanner::addAccelerationForce(State *frontState, State *currentState, State *backState) {
    AccelerationForce force;
    force.setParam(0, frontState);
    force.setParam(1, currentState);
    force.setParam(2, backState);
    optim_.addForce(force);
}

void TEBPlanner::addAccelerationStartForce(State *currentState) {
    AccelerationStartForce force;
    force.setParam(0, &start_);
    force.setParam(1, currentState);
    optim_.addForce(force);
}

void TEBPlanner::addAccelerationEndForce(State *currentState) {
    AccelerationEndForce force;
    force.setParam(0, currentState);
    force.setParam(1, &end_);
    optim_.addForce(force);
}

void TEBPlanner::addObstacleForce(State *obstacleState, State *currentState) {
    ObstacleForce force;
    force.setParam(0, obstacleState);
    force.setParam(1, currentState);
    optim_.addForce(force);
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

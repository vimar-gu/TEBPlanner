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

            // start of the trajectory vector

            if (i == 0) {

            }

            // end of the trajectory vector

            else if (i == trajVec_.size() - 1) {

            }

            // default condition

            else {

            }

            // do the optimization

            optimizeState();
            clear();
        }
    }
}

void TEBPlanner::initOptimize() {

}

void TEBPlanner::optimizeState() {

}

void TEBPlanner::clear() {

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

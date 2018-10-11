#include "Tebplanner.h"
#include "Utils.h"
#include <QDebug>


void TEBPlanner::plan() {

}

void TEBPlanner::initOptimize() {

}

void TEBPlanner::optimizeState() {

}

void TEBPlanner::clear() {

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

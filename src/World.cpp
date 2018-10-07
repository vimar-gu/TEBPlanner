#include <QQmlApplicationEngine>
#include <QTimer>
#include <QDebug>
#include "World.h"
#include "config.h"

// init the world in a naive way, maybe improve later

CWorld::CWorld() {
    for (int i = 0; i < ROBOT_NUMBER; i++) {
        Robot robot(ORIGIN_X + 200, ORIGIN_Y + i * 50);
        robotVec.push_back(robot);
    }
    for (int i = 0; i < OBSTACLE_NUMBER; i++) {
        Obstacle obs(ORIGIN_X, ORIGIN_Y + i * 50);
        obsVec.push_back(obs);
    }
    target.setPos(CGeoPoint(200, 200));
}

// connected to the start button on the board

void CWorld::start() {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fresh()));
    timer->start(10);
}

// update the trajectory points according to the change of the field

void CWorld::fresh() {
    freshTraj();
    emit needDraw();
}

// fresh traj

void CWorld::freshTraj() {
    for (Robot robot : robotVec) {
        traj.plan(robot.pos(), target.pos(), obsVec);
    }
}

// add a new obstacle to a random place regardless of the collision

void CWorld::addObstacle() {
    int x = rand() % 10;
    int y = rand() % 10;
    Obstacle obs(ORIGIN_X + x * 50, ORIGIN_Y + y * 50);
    obsVec.push_back(obs);
}

// delete the selected obstacle according to the mouse event

void CWorld::deleteObstacle(MoveObj* obj) {
    auto obsIterator = find_if(obsVec.begin(), obsVec.end(), [=](Obstacle& obs){ return obj->pos() == obs.pos(); });
    if (obsIterator != obsVec.end()) obsVec.erase(obsIterator);
}

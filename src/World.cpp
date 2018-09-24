#include <QQmlApplicationEngine>
#include <QTimer>
#include "World.h"
#include "config.h"

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

void CWorld::start() {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fresh()));
    timer->start(10);
}

void CWorld::fresh() {
    freshTraj();
    emit needDraw();
}

void CWorld::freshTraj() {
    for (Robot robot : robotVec) {
        traj.plan(robot.pos(), target.pos(), obsVec);
    }
}

void CWorld::addEnemyObstacle() {

}

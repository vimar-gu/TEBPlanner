#include <QQmlApplicationEngine>
#include <QTimer>
#include "World.h"
#include "config.h"

CWorld::CWorld() {
    for (int i = 0; i < OBSTACLE_NUMBER; i++) {
        Obstacle obs(ORIGIN_X, ORIGIN_Y + i * 50);
        obsVec.push_back(obs);
    }
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

}

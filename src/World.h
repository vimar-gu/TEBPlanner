#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include "singleton.h"
#include "Model.h"
#include "Trajectory.h"
#include <QObject>
#include <QString>
using namespace std;

class CWorld : public QObject {
    Q_OBJECT
public:
    CWorld();
    void start();
    void freshTraj();
    void addEnemyObstacle();
    vector<Robot> robotVec;
    vector<Obstacle> obsVec;
    Trajectory traj;
    MoveObj target;
signals:
    void needDraw();
public slots:
    void fresh();
};

typedef Singleton<CWorld> World;

#endif // WORLD_H

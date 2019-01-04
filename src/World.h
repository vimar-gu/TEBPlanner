#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <vector>
#include "singleton.h"
#include "Model.h"
#include "Trajectory.h"
#include <QObject>
#include <QString>
#include "config.h"

using namespace std;

class CWorld : public QObject {
    Q_OBJECT
public:
    CWorld();
    void start();
    void freshTraj();
    void addObstacle();
    void deleteObstacle(MoveObj* obj);
    void setTrajMethod(int method) {}
    vector<Robot> robotVec;
    vector<Obstacle> obsVec;
    Trajectory traj;
    MoveObj target;
signals:
    void needDraw();
public slots:
    void fresh();
};

// ensure there is only one world during the run

typedef Singleton<CWorld> World;

#endif // WORLD_H

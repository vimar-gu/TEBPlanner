#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include "singleton.h"
#include "Model.h"
#include "Trajectory.h"
using namespace std;

class CWorld
{
public:
    CWorld();
    void start();
signals:
    void needDraw();
public slots:
    void fresh();
private:
    vector<Robot> robotVec;
    vector<Obstacle> obsVec;
};

typedef Singleton<CWorld> World;

#endif // WORLD_H

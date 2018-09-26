#ifndef TEBPLANNER_H
#define TEBPLANNER_H
#include "Model.h"


class TEBPlanner
{
public:
    TEBPlanner();
    TEBPlanner(vector<CGeoPoint>& trajVec, CGeoPoint start, CGeoPoint end, vector<Obstacle> obs);
};

#endif // TEBPLANNER_H

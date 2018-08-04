#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "singleton.h"

class CTrajectory
{
public:
    CTrajectory();
};

typedef Singleton<CTrajectory> Trajectory;

#endif // ALGORITHM_H

#ifndef TEBFORCE_H
#define TEBFORCE_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "Model.h"
#include "config.h"
#include "Utils.h"
using namespace std;

class TEBForce {
public:
    TEBForce() {}
    virtual ~TEBForce() {
        vector<CVector>().swap(params_);
    }
    void resize(int n) {
        params_.resize(n);
        for (auto& param : params_) {
            param = nullptr;
        }
    }
    void setParam(int i, State* value) {
        params_[i] = value;
    }
    virtual CVector calcForce() = 0;
    double ReLU(double x) { return max(x, 0); }
private:
    vector<State*> params_;
    double forceMod_;
    double forceDir_;
};

class VelocityForce : public TEBForce {
public:
    VelocityForce() { this->resize(2); }
    CVector calcForce() {
        CGeoPoint frontPos = params_[0]->pos();
        CGeoPoint currentPos = params_[1]->pos();
        CVector currentVel = (frontPos - currentPos) * FRAME_NUMBER;

        forceMod_ = ReLU(currentVel.mod() - MAX_VELOCITY);
        forceDir_ = (frontPos - currentPos).dir();
        return polar2Vector(forceMod_, forceDir_);
    }
};

class AccelerationForce : public TEBForce {
public:
    AccelerationForce() { this->resize(3); }
    CVector calcForce() {
        CGeoPoint frontPos = params_[0]->pos();
        CGeoPoint currentPos = params_[1]->pos();
        CGeoPoint backPos = params_[2]->pos();
        CVector frontVel = (currentPos - frontPos) * FRAME_NUMBER;
        CVector backVel = (backPos - currentPos) * FRAME_NUMBER;
        CVector currentAcc = (backVel - frontVel) * FRAME_NUMBER;

        forceMod_ = ReLU(currentAcc.mod() - MAX_ACCELERATION);
        forceDir_ = (frontPos - currentPos).dir();
        return polar2Vector(forceMod_, forceDir_);
    }
};

class ObstacleForce : public TEBForce {
public:
    ObstacleForce() { this->resize(2); }
    CVector calcForce() {
        CGeoPoint obsPos = params_[0]->pos();
        CGeoPoint currentPos = params_[1]->pos();
        CVector fromObsVec = currentPos - obsPos;

        forceMod_ = ReLU(MIN_OBSTACLE_DISTANCE - fromObsVec.mod());
        forceDir_ = fromObsVec.dir();
        return polar2Vector(forceMod_, forceDir_);
    }
};

#endif // TEBFORCE_H

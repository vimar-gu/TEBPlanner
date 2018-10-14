#ifndef TEBFORCE_H
#define TEBFORCE_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <QDebug>
#include "Model.h"
#include "config.h"
#include "Utils.h"
using namespace std;

class TEBForce {
public:
    TEBForce() {}
    void resize(int n) {
        params_.resize(n);
        for (auto& param : params_) {
            param = nullptr;
        }
    }
    void setParam(int i, State* value) {
        params_[i] = value;
    }
    virtual CVector calcForce() { return CVector(); }
    virtual void toStream() { qDebug() << "TEBForce"; }
    double ReLU(double x) { return max(x, 0.0); }
public:
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
    void toStream() { qDebug() << "VelocityForce"; }
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
    void toStream() { qDebug() << "AccelerationForce"; }
};

class AccelerationStartForce : public TEBForce {
public:
    AccelerationStartForce() { this->resize(2); }
    CVector calcForce() {
        CVector startVel = params_[0]->vel();
        CGeoPoint startPos = params_[0]->pos();
        CGeoPoint currentPos = params_[1]->pos();
        CVector currentVel = (currentPos - startPos) * FRAME_NUMBER;
        CVector currentAcc = (currentVel - startVel) * FRAME_NUMBER * 2;

        forceMod_ = ReLU(currentAcc.mod() - MAX_ACCELERATION);
        forceDir_ = (startPos - currentPos).dir();
        return polar2Vector(forceMod_, forceDir_);
    }
    void toStream() { qDebug() << "AccelerationStartForce"; }
};

class AccelerationEndForce : public TEBForce {
public:
    AccelerationEndForce() { this->resize(2); }
    CVector calcForce() {
        CGeoPoint currentPos = params_[0]->pos();
        CVector endVel = params_[1]->vel();
        CGeoPoint endPos = params_[1]->pos();
        CVector currentVel = (endPos - currentPos) * FRAME_NUMBER;
        CVector currentAcc = (endVel - currentVel) * FRAME_NUMBER * 2;

        forceMod_ = ReLU(currentAcc.mod() - MAX_ACCELERATION);
        forceDir_ = (endPos - currentPos).dir();
        return polar2Vector(forceMod_, forceDir_);
    }
    void toStream() { qDebug() << "AccelerationEndForce"; }
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
    void toStream() { qDebug() << "ObstacleForce"; }
};

#endif // TEBFORCE_H

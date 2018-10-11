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
private:
    vector<State*> params_;
};

class VelocityForce : public TEBForce {
public:
    VelocityForce() { this->resize(2); }
    CVector calcForce() {
        CGeoPoint frontPos = params_[0]->pos();
        CGeoPoint currentPos = params_[1]->pos();
        CVector currentVel = (frontPos - currentPos) * FRAME_NUMBER;

        double forceMod = max(currentVel.mod() - MAX_VELOCITY, 0);
        double forceDir = (frontPos - currentPos).dir();
        return polar2Vector(forceMod, forceDir);
    }
}

#endif // TEBFORCE_H

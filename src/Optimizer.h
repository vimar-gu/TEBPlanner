#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "Model.h"
#include "Tebforce.h"

class Optimizer {
public:
    Optimizer() {}
    void addForce(TEBForce* force) {
        forces_.push_back(force);
    }
    void init();
    void optimize(int innerLoop, vector<State*>& trajVec, int index);
    void clear() { forces_.clear(); }
    double getForcesSize() { return forces_.size(); }
    CVector calcTotalForce();
private:
    vector<TEBForce*> forces_;
};

#endif // OPTIMIZER_H

#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "Model.h"
#include "Tebforce.h"

class Optimizer {
public:
    Optimizer() {}
    void addForce(TEBForce force) {
        forces_.push_back(force);
    }
    void optimize(int innerLoop);
    void clear() { vector<TEBForce>().swap(forces_); }
private:
    vector<TEBForce> forces_;
    State* current;
};

#endif // OPTIMIZER_H

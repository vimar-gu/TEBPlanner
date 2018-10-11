#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "Model.h"
#include "Tebforce.h"

class Optimizer {
public:
    Optimizer(State* s) : current(s) {}
    void addForce(TEBForce force) {
        forces_.push_back(force);
    }
    void optimize(int innerLoop);
private:
    vector<TEBForce> forces_;
    State* current;
};

#endif // OPTIMIZER_H

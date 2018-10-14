#include "Optimizer.h"

void Optimizer::init() {

}

void Optimizer::prune() {

}

void Optimizer::optimize(int innerLoop) {
    int index = 0;

    while (index < innerLoop) {
        index++;

        for (TEBForce& force : forces_) {
            CVector forceVec = force.calcForce();
        }
    }
}

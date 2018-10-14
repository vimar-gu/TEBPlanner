#include "Optimizer.h"
#include <QDebug>

void Optimizer::init() {

}

void Optimizer::prune() {

}

void Optimizer::optimize(int innerLoop) {
    int index = 0;

    while (index < innerLoop) {
        index++;

        CVector totalForce(0, 0);
        for (TEBForce* force : forces_) {
            totalForce = totalForce + force->calcForce();
        }
//        qDebug() << totalForce.mod();
    }
}

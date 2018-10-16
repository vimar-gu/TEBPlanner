#include "Optimizer.h"
#include <QDebug>

void Optimizer::init() {

}

void Optimizer::optimize(int innerLoop) {
    int index = 0;

    while (index < innerLoop) {
        index++;

        CVector totalForce = calcTotalForce();
//        qDebug() << totalForce.mod();
    }
}

CVector Optimizer::calcTotalForce() {
    CVector totalForce(0, 0);
    for (TEBForce* force : forces_) {
        totalForce = totalForce + force->calcForce();
    }
    return totalForce;
}

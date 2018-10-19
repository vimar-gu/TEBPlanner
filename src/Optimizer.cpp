#include "Optimizer.h"
#include <QDebug>

void Optimizer::init() {

}

void Optimizer::optimize(int innerLoop, vector<State*>& trajVec, int index) {
    int loop = 0;
    CVector lastLoss(0, 0);
    CVector currentLoss(0, 0);
    CVector gt(0, 0);
    CVector mt(0, 0);
    double vt = 0;

    while (loop < innerLoop) {
        loop++;

        currentLoss = calcTotalForce();
        gt = lastLoss - currentLoss;
        mt = (mt * BETA_1 + gt * (1 - BETA_1));
        vt = (vt * BETA_2 + pow(gt.mod(), 2) * (1 - BETA_2));
        CVector deltaVec = mt * (ALPHA / (sqrt(vt) + EPSILON));

        if (gt.mod() > 0) {
//            qDebug() << gt.mod() << mt.mod() << sqrt(vt) << deltaVec.mod();
//            qDebug() << gt.mod() << deltaVec.dir();
            for (int i = index; i < trajVec.size(); i++)
                trajVec[i]->setPos(trajVec[i]->pos() + -deltaVec);
        }

        lastLoss = currentLoss;
//        qDebug() << totalForce.mod();
    }
}

CVector Optimizer::calcTotalForce() {
    CVector totalForce(0, 0);
    for (TEBForce* force : forces_) {
        CVector deltaForce = force->calcForce();
        totalForce = totalForce + deltaForce;
    }
    return totalForce;
}

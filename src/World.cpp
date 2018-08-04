#include "World.h"
#include <QTimer>

CWorld::CWorld()
{

}

void CWorld::start() {
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fresh()));
    timer->start(50);
}

#include "Interaction.h"
#include "World.h"

Interaction::Interaction(QObject *parent) : QObject(parent) {

}

void Interaction::setVision() {
    World::instance()->start();
}

void Interaction::addObstacle() {
    World::instance()->addObstacle();
}

void Interaction::setTrajectoryMethod(int method) {
    World::instance()->setTrajMethod(method);
}

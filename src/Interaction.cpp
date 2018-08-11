#include "Interaction.h"
#include "World.h"

Interaction::Interaction(QObject *parent) : QObject(parent) {

}

void Interaction::setVision(){
    World::instance()->start();
}

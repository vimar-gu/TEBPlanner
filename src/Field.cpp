#include <QDebug>
#include "field.h"
#include "World.h"
#include "Model.h"

namespace{
    const static QColor COLOR_BLUE(210,210,255);
    const static QColor COLOR_YELLOW(241,231,36);
    const static QColor COLOR_PINK(255,63,149);
    const static QColor COLOR_GREEN(105,255,0);
    const static QColor COLOR_DARK_ORANGE(255,120,50);
    const static QColor COLOR_ORANGE(255,170,85);
}

Field::Field(QQuickItem *parent): QQuickPaintedItem(parent), pixmap(nullptr), pen(Qt::white,1) {
    connect(World::instance(),SIGNAL(needDraw()),this,SLOT(draw()));
    pixmap = new QPixmap(QSize(600, 500));
    pixmapPainter.begin(pixmap);
    area = QRect(0,0,600,500);
}

void Field::draw() {
    pixmap->fill(COLOR_BLUE);
    pixmapPainter.strokePath(painterPath, pen);
    fillField();
    this->update(area);
}

void Field::paint(QPainter* painter){
    painter->drawPixmap(area,*pixmap);
}

void Field::mousePressEvent(QMouseEvent *e) {
    pressed = e->buttons();
//    checkClosestRobot(rx(e->x()),ry(e->y()));
//    start = end = rp(e->pos());
    switch(pressed){
    case Qt::LeftButton:
        leftPressEvent(e);
        break;
    case Qt::RightButton:
        rightPressEvent(e);
        break;
    default:
        break;
    }
}

void Field::mouseMoveEvent(QMouseEvent *e){
//    end = rp(e->pos());
    switch(pressed){
    case Qt::LeftButton:
        leftMoveEvent(e);
        break;
    case Qt::RightButton:
        rightMoveEvent(e);
        break;
    default:
        break;
    }
}

void Field::mouseReleaseEvent(QMouseEvent *e){
    switch(pressed){
    case Qt::LeftButton:
        leftReleaseEvent(e);
        break;
    case Qt::RightButton:
        rightReleaseEvent(e);
        break;
    default:
        break;
    }
    resetAfterMouseEvent();
}

void Field::resetAfterMouseEvent(){
    pressed = 0;
    pressedRobot = false;
    start = end = QPoint(-9999,-9999);
}

void Field::checkClosestRobot(double x,double y){
//    double limit = carDiameter*carDiameter/4;
//    auto& vision = GlobalData::instance()->maintain[0];
//    for(int color=BLUE;color<=YELLOW;color++){
//        for(int j=0;j<vision.robotSize[color];j++){
//            auto& robot = vision.robot[color][j];
//            if(distance2(robot.pos.x()-x,robot.pos.y()-y)<limit){
//                robotID = robot.id;
//                robotTeam = color;
//                pressedRobot = true;
//                return;
//            }
//        }
//    }
    pressedRobot = false;
}

void Field::leftMoveEvent(QMouseEvent *e){
    if(pressedRobot){
//        Simulator::instance()->setRobot(rx(e->x())/1000.0,ry(e->y())/1000.0,robotID,robotTeam == YELLOW);
    }else{
//        Simulator::instance()->setBall(rx(e->x())/1000.0,ry(e->y())/1000.0);
    }
}

void Field::leftPressEvent(QMouseEvent *e){
    if(pressedRobot){
//        Simulator::instance()->setRobot(rx(e->x())/1000.0,ry(e->y())/1000.0,robotID,robotTeam == YELLOW);
    }else{
//        Simulator::instance()->setBall(rx(e->x())/1000.0,ry(e->y())/1000.0);
    }
}

void Field::leftReleaseEvent(QMouseEvent *e){

}

void Field::rightMoveEvent(QMouseEvent *e){
    QLineF line(start,end);
    if(pressedRobot){
//        displayData = -line.angle();
//        if(displayData<-180) displayData += 360;
//        Simulator::instance()->setRobot(start.x()/1000.0,start.y()/1000.0,robotID,robotTeam == YELLOW,displayData);
    }else{
//        displayData = line.length()/1000.0;
    }
}

void Field::rightPressEvent(QMouseEvent *e){

}

void Field::rightReleaseEvent(QMouseEvent *e){
//    QLineF line(start,end);
    if(!pressedRobot){
//        Simulator::instance()->setBall(start.x()/1000.0,start.y()/1000.0,line.dx()/1000.0,line.dy()/1000.0);
    }
}

void Field::fillField() {
    for (auto robot : World::instance()->getRobotVec()) {

    }
    for (auto obs : World::instance()->getObsVec()) {

    }
    for (auto trajPos : World::instance()->getTrajVec()) {

    }
}

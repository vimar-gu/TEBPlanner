#include <QDebug>
#include "field.h"
#include "config.h"

namespace{
    const static QColor COLOR_BLUE(210,210,255);
    const static QColor COLOR_YELLOW(241,231,36);
    const static QColor COLOR_PINK(255,63,149);
    const static QColor COLOR_GREEN(105,255,0);
    const static QColor COLOR_DARK_ORANGE(255,120,50);
    const static QColor COLOR_ORANGE(255,170,85);
}

Field::Field(QQuickItem *parent): QQuickPaintedItem(parent), pixmap(nullptr), pen(Qt::white,1) {
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemAcceptsInputMethod, true);

    connect(World::instance(),SIGNAL(needDraw()),this,SLOT(draw()));
    pixmap = new QPixmap(QSize(720, 720));
    pixmapPainter.begin(pixmap);
    area = QRect(0,0,720,720);
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
    checkClosestRobot(e->x(),e->y());
    switch(pressed){
    case Qt::LeftButton:
        leftPressEvent(e);
        break;
    default:
        break;
    }
}

void Field::mouseMoveEvent(QMouseEvent *e){
    switch(pressed){
    case Qt::LeftButton:
        leftMoveEvent(e);
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

void Field::checkClosestRobot(double x, double y){
    double limit = OBSTACLE_RADIUS;
    pressedRobot = false;
    for (auto& obs : World::instance()->obsVec) {
        if (obs.pos().dist(CGeoPoint(x, y)) < limit) {
            pressedRobot = true;
            movingObj = &obs;
        }
    }
    for (auto& robot : World::instance()->robotVec) {
        if (robot.pos().dist(CGeoPoint(x, y)) < limit) {
            pressedRobot = true;
            movingObj = &robot;
        }
    }
    if (World::instance()->target.pos().dist(CGeoPoint(x, y)) < limit) {
        pressedRobot = true;
        movingObj = &World::instance()->target;
    }
}

void Field::leftMoveEvent(QMouseEvent *e){
    if(pressedRobot){
        movingObj->setPos(CGeoPoint(e->x(), e->y()));
    }
}

void Field::leftPressEvent(QMouseEvent *e){
    if(pressedRobot){
        movingObj->setPos(CGeoPoint(e->x(), e->y()));
    }
}

void Field::leftReleaseEvent(QMouseEvent *e){

}

void Field::paintRobot(const QColor &color, qreal x, qreal y) {
    static float radius = OBSTACLE_RADIUS;
    pixmapPainter.setBrush(QBrush(color));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);
}

void Field::paintObstacle(const QColor &color, qreal x, qreal y) {
    static float radius = OBSTACLE_RADIUS;
    pixmapPainter.setBrush(QBrush(color));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);
}

void Field::paintTarget(const QColor &color, qreal x, qreal y) {
    static float radius = OBSTACLE_RADIUS;
    pixmapPainter.setBrush(QBrush(color));
    pixmapPainter.setPen(Qt::NoPen);
    pixmapPainter.drawEllipse(x - radius, y - radius, 2 * radius, 2 * radius);
}

void Field::paintTraj(const QColor &color, qreal x, qreal y) {
    static float radius = OBSTACLE_RADIUS / 2;
    pixmapPainter.setBrush(QBrush(Qt::NoBrush));
    pixmapPainter.setPen(QPen(color, 2));
    pixmapPainter.drawLine(QPointF(x - radius, y - radius), QPointF(x + radius, y + radius));
    pixmapPainter.drawLine(QPointF(x - radius, y + radius), QPointF(x + radius, y - radius));
}

void Field::fillField() {
    for (auto robot : World::instance()->robotVec) {
        paintRobot(COLOR_YELLOW, robot.pos().x(), robot.pos().y());
    }
    for (auto obs : World::instance()->obsVec) {
        paintObstacle(COLOR_PINK, obs.pos().x(), obs.pos().y());
    }
    for (auto trajPos : World::instance()->traj.trajVec) {
        paintTraj(COLOR_DARK_ORANGE, trajPos.x(), trajPos.y());
    }
    paintTarget(COLOR_ORANGE, World::instance()->target.pos().x(), World::instance()->target.pos().y());
}

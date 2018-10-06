#ifndef FIELD_H
#define FIELD_H
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPainterPath>
#include <QImage>
#include "World.h"

class Field : public QQuickPaintedItem {
    Q_OBJECT
public:
    void paint(QPainter* painter) override;
    Field(QQuickItem *parent = 0);
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
public slots:
    void draw();
private:
    void initField();
    void fillField();
    void paintRobot(const QColor &robotColor, const QColor &dirColor, qreal x, qreal y, qreal dir);
    void paintObstacle(const QColor &color, qreal x, qreal y);
    void paintTarget(const QColor &color, qreal x, qreal y);
    void paintTraj(const QColor &color, qreal x, qreal y);
    void checkClosestRobot(double x,double y);
    void leftMoveEvent(QMouseEvent *e);
    void leftPressEvent(QMouseEvent *e);
    void leftReleaseEvent(QMouseEvent *e);
    void middleReleaseEvent(QMouseEvent *e);
    void resetAfterMouseEvent();
    QPixmap *pixmap;
    QPainter pixmapPainter;
    QPainterPath painterPath;
    QPen pen;
    QRect area;
    MoveObj *movingObj;
    int pressed;
    bool pressedRobot;
    QPoint start;
    QPoint end;
};

#endif // FIELD_H

#ifndef FIELD_H
#define FIELD_H
#include <QQuickPaintedItem>
#include <QPainter>
#include <QPainterPath>
#include <QImage>

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
    void paintObstacle(const QColor &color, qreal x, qreal y);
    void checkClosestRobot(double x,double y);
    void leftMoveEvent(QMouseEvent *);
    void leftPressEvent(QMouseEvent *);
    void leftReleaseEvent(QMouseEvent *);
    void rightMoveEvent(QMouseEvent *);
    void rightPressEvent(QMouseEvent *);
    void rightReleaseEvent(QMouseEvent *);
    void resetAfterMouseEvent();
    QPixmap *pixmap;
    QPainter pixmapPainter;
    QPainterPath painterPath;
    QPen pen;
    QRect area;
    int pressed;
    bool pressedRobot;
    QPoint start;
    QPoint end;
};

#endif // FIELD_H

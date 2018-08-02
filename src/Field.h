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
signals:
public slots:
    void draw();
private:
    void initField();
    void fillField();
    QPixmap *pixmap;
    QPainter pixmapPainter;
    QPainterPath painterPath;
    QPen pen;
    QRect area;
};

#endif // FIELD_H

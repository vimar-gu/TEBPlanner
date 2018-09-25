#ifndef INTERACTION_H
#define INTERACTION_H
#include <QObject>
#include <string>

class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = 0);
    Q_INVOKABLE void setVision();
    Q_INVOKABLE void addObstacle();
    Q_INVOKABLE void setTrajectoryMethod(int method);
};

#endif // INTERACTION_H

#ifndef INTERACTION_H
#define INTERACTION_H
#include <QObject>
#include <string>

class Interaction : public QObject
{
    Q_OBJECT
public:
    explicit Interaction(QObject *parent = 0);
};

#endif // INTERACTION_H

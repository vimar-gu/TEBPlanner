#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
using namespace std;

class pos {
public:
    pos() : x_(0), y_(0) {}
    pos(int x, int y) { x_ = x; y_ = y; }
    double x() { return x_; }
    double y() { return y_; }
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    pos operator+(vel v) { return pos(x_ + v.x(), y_ + v.y()); }
    vel operator-(pos p) { return vel(x_ - p.x(), y_ - p.y()); }
private:
    double x_;
    double y_;
};

class vel {
public:
    vel() : x_(0), y_(0) {}
    vel(int x, int y) { x_ = x; y_ = y; }
    double x() { return x_; }
    double y() { return y_; }
    void setX(double x) { x_ = x; }
    void setY(double y) { y_ = y; }
    vel operator+(vel p) { return vel(x_ + p.x(), y_ + p.y()); }
    vel operator-(vel p) { return vel(x_ - p.x(), y_ - p.y()); }
private:
    double x_;
    double y_;
};

class Car {
public:
    Car() {}
private:
    pos pos_;
    double dir_;
    vel vel_;
    double rotVel_;
};

class Obstacle {
public:
    Obstacle() {}
private:
    pos pos_;
    vel vel_;
};

vector<pos> posList;

#endif // MODEL_H

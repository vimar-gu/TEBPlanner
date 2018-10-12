#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include "config.h"

using namespace std;

class CVector {
public:
    CVector() :	_x(0), _y(0) {}
    CVector(double x, double y) : _x(x), _y(y) {}
    CVector(const CVector& v) :	_x(v.x()), _y(v.y()) {}
    double mod() const { return sqrt(_x * _x + _y * _y); }
    double dir() const { return atan2(_y, _x);}
    CVector rotate(double angle) const;
    double x() const { return _x; }
    double y() const { return _y; }
    void print()
    {
        cout << "vector = " << _x << " " << _y << endl;
    }
    CVector operator +(const CVector& v) const { return CVector(_x + v.x(), _y + v.y()); }
    CVector operator -(const CVector& v) const { return CVector(_x - v.x(), _y - v.y()); }
    CVector operator *(double a) const { return CVector(_x * a, _y * a); } //向量数乘
    double operator *(CVector b) const { return double(_x * b.x() + _y * b.y()); } //向量点乘
    CVector operator /(double a) const { return CVector(_x / a, _y / a); }
    CVector operator -() const { return CVector(-1 * _x, -1 * _y); }
private:
    double _x, _y;
};

class CGeoPoint {
public:
    CGeoPoint() : _x(0), _y(0) {}
    CGeoPoint(double x, double y) : _x(x), _y(y) {}
    CGeoPoint(const CGeoPoint& p) : _x(p.x()), _y(p.y()) {}
    double x() const { return _x; }
    double y() const { return _y; }
    void print()
    {
        std::cout << "pos = " << _x << " " << _y << std::endl;
    }
    bool operator ==(const CGeoPoint& rhs) { return ((this->x() == rhs.x()) && (this->y() == rhs.y())); }
    CGeoPoint operator +(const CVector& v) const { return CGeoPoint(_x + v.x(), _y + v.y()); }
    CGeoPoint operator *(const double& a) const { return CGeoPoint(_x * a, _y * a); }
    CVector operator -(const CGeoPoint& p) const { return CVector(_x - p.x(), _y - p.y()); }
    double dist(const CGeoPoint& p) const { return CVector(p - CGeoPoint(_x, _y)).mod(); }
    CGeoPoint midPoint(const CGeoPoint& p) const{ return CGeoPoint((_x + p.x()) / 2, (_y + p.y()) / 2); }
private:
    double _x, _y;
};

struct MoveObj {
public:
    MoveObj(double r = OBSTACLE_RADIUS):_radius(r) {}
    MoveObj(CGeoPoint pos, double r = OBSTACLE_RADIUS) : _pos(pos), _radius(r) {}
    MoveObj(double x, double y, double r = OBSTACLE_RADIUS) : _pos(CGeoPoint(x, y)), _radius(r) {}
    CGeoPoint pos() const { return _pos; }
    CVector vel() const { return _vel; }
    void setPos(const CGeoPoint& pos) { _pos = CGeoPoint(pos); }
    void setVel(const CVector& vel) { _vel = CVector(vel); }
    CGeoPoint _pos;
    CVector _vel;
    double _radius;
    bool checkCollision(const CGeoPoint& p)
    {
//        cout << "margin = " << margin(p) << endl;
        if (margin(p) > 0.0)
            return false;
        else return true;
    }
    double margin(const CGeoPoint& p)
    {
//        cout << "_pos = " << _pos.x() << " " << _pos.y() << endl;
//        cout << "p = " << p.x() << " " << p.y() << endl;
//        cout << "radius = " << _radius << endl;
//        cout << "r_radius = " << ROBOT_RADIUS << endl;
//        cout << "dist = " << _pos.dist(p)<< endl;
        return _pos.dist(p) - _radius - ROBOT_RADIUS;
    }
};

typedef MoveObj Obstacle;

class Robot : public MoveObj {
public:
    Robot(double r = ROBOT_RADIUS) : _radius(r){}
    Robot(CGeoPoint p, double r = ROBOT_RADIUS) : MoveObj(p),_radius(r) {}
    Robot(double x, double y, double r = ROBOT_RADIUS) : MoveObj(CGeoPoint(x, y)), _radius(r) {}
    double dir() const { return _dir; }
    double rotVel() const { return _rotVel; }
    void setDir(const double& dir) { _dir = dir; }
    void setRotVel(const double& rotVel) { _rotVel = rotVel; }
    double _radius;
private:
    double _dir;
    double _rotVel;
};

typedef Robot State;

class RoundObstacle : private Obstacle {

};

class RectObstacle : private Obstacle {

};

#endif // MODEL_H

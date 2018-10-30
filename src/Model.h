#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "config.h"

using namespace std;

// the class of vectors

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
    bool operator ==(const CVector& rhs) { return ((this->x() == rhs.x()) && (this->y() == rhs.y())); }
    CVector operator +(const CVector& v) const { return CVector(_x + v.x(), _y + v.y()); }
    CVector operator -(const CVector& v) const { return CVector(_x - v.x(), _y - v.y()); }
    CVector operator *(double a) const { return CVector(_x * a, _y * a); } //向量数乘
    double operator *(CVector b) const { return double(_x * b.x() + _y * b.y()); } //向量点乘
    CVector operator /(double a) const { return CVector(_x / a, _y / a); }
    CVector operator -() const { return CVector(-1 * _x, -1 * _y); }
private:
    double _x, _y;
};

// the class of points

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

// the class of lines

class CGeoLine {
public:
    CGeoLine() {}
    CGeoLine(const CGeoPoint& p1, const CGeoPoint& p2) : _p1(p1), _p2(p2) { calABC(); }
    CGeoLine(const CGeoPoint& p, double angle) : _p1(p), _p2(p.x() + std::cos(angle), p.y() + std::sin(angle)) { calABC(); }
    void calABC() {
        if(_p1.y() == _p2.y()) {
            _a = 0;
            _b = 1;
            _c = -1.0 * _p1.y();
        } else {
            _a = 1;
            _b = -1.0 * (_p1.x() - _p2.x()) / (_p1.y() - _p2.y());
            _c = (_p1.x()*_p2.y() - _p1.y()*_p2.x()) / (_p1.y() - _p2.y());
        }
    }
    CGeoPoint projection(const CGeoPoint& p) const {
        if (_p2.x() == _p1.x()) {
            return CGeoPoint(_p1.x(), p.y());
        } else {
            double k = (_p2.y() - _p1.y()) / (_p2.x() - _p1.x());
            double x = (k * k * _p1.x() + k * (p.y() - _p1.y()) + p.x()) / (k * k + 1);
            double y = k * (x - _p1.x()) + _p1.y();
            return CGeoPoint(x, y);
        }
    }
    CGeoPoint point1() const { return _p1; }
    CGeoPoint point2() const { return _p2; }
    bool operator==(const CGeoLine& rhs) {
        return ((this->point1().x() == rhs.point1().x()) && (this->point1().y() == rhs.point1().y())
            && (this->point2().x() == rhs.point2().x()) && (this->point2().y() == rhs.point2().y()));
    }
    const double& a() const{ return _a; }
    const double& b() const{ return _b; }
    const double& c() const{ return _c; }
private:
    CGeoPoint _p1, _p2;
    double _a, _b, _c;
};

// the class of segments

class CGeoSegment: public CGeoLine {
public:
    CGeoSegment() {}
    CGeoSegment(const CGeoPoint& p1, const CGeoPoint& p2) : CGeoLine(p1, p2), _start(p1), _end(p2) {
        _compareX = std::abs(p1.x() - p2.x()) > std::abs(p1.y() - p2.y());
        _center = CGeoPoint((p1.x()+p2.x())/2, (p1.y()+p2.y())/2);
    }
    bool IsPointOnLineOnSegment(const CGeoPoint& p) const {
        if(_compareX){
            return p.x() > (std::min)(_start.x(), _end.x()) && p.x() < (std::max)(_start.x(), _end.x());
        }
        return p.y() > (std::min)(_start.y(), _end.y()) && p.y() < (std::max)(_start.y(), _end.y());
    }
    double dist2Point(const CGeoPoint& p) {
        CGeoPoint tmpProj = projection(p);
        if (IsPointOnLineOnSegment(tmpProj)) return p.dist(tmpProj);
        else return min(_start.dist(p), _end.dist(p));
    }
    const CGeoPoint& start() const { return _start; }
    const CGeoPoint& end() const { return _end; }
    const CGeoPoint& center() {return _center;}

private:
    CGeoPoint _start;
    CGeoPoint _end;
    CGeoPoint _center;
    bool _compareX;
};

class MoveObj {
public:
    MoveObj() : _pos(CGeoPoint(0, 0)), _vel(CVector(0, 0)), _dir(0), _rotVel(0), _radius(OBSTACLE_RADIUS) {}
    MoveObj(double r) : _pos(CGeoPoint(0, 0)), _vel(CVector(0, 0)), _dir(0), _rotVel(0), _radius(r) {}
    MoveObj(CGeoPoint pos, double r = OBSTACLE_RADIUS) : _pos(pos), _vel(CVector(0, 0)), _dir(0), _rotVel(0), _radius(r) {}
    MoveObj(double x, double y, double r = OBSTACLE_RADIUS) : _pos(CGeoPoint(x, y)), _vel(CVector(0, 0)), _dir(0), _rotVel(0), _radius(r) {}
    bool operator==(const MoveObj& rhs) {
        return (this->pos() == rhs.pos() && this->vel() == rhs.vel() && this->dir() == rhs.dir() && this->rotVel() == rhs.rotVel());
    }
    CGeoPoint pos() const { return _pos; }
    CVector vel() const { return _vel; }
    double dir() const { return _dir; }
    double rotVel() const { return _rotVel; }
    void setPos(const CGeoPoint& pos) { _pos = CGeoPoint(pos); }
    void setVel(const CVector& vel) { _vel = CVector(vel); }
    void setDir(const double& dir) { _dir = dir; }
    void setRotVel(const double& rotVel) { _rotVel = rotVel; }
    CGeoPoint _pos;
    CVector _vel;
    double _dir;
    double _rotVel;
    double _radius;
};

// define the obstacle the same as moveobj

typedef MoveObj Robot;

typedef MoveObj State;

class Obstacle : public MoveObj {
public:
    Obstacle() : MoveObj() {}
    Obstacle(double x, double y) : MoveObj(x, y) {}
    bool checkSegment(const CGeoPoint& m, const CGeoPoint& n) {
        CGeoSegment tmpSeg(m, n);
        return tmpSeg.dist2Point(_pos) - _radius - ROBOT_RADIUS < 0.0;
    }
    bool checkPoint(const CGeoPoint& p) { // true if the point is not safe
        return margin(p) < 0.0;
    }
    double margin(const CGeoPoint& p) {
        return _pos.dist(p) - _radius - ROBOT_RADIUS;
    }
};

class RoundObstacle : private Obstacle {

};

class RectObstacle : private Obstacle {

};

#endif // MODEL_H

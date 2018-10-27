#ifndef RRTPLANNER_H
#define RRTPLANNER_H
#include "Model.h"


struct RRTNode {
    RRTNode() : ID(0), pos(CGeoPoint(0, 0)), parentID(-1), depth(0) {}
    RRTNode(const CGeoPoint& p) : ID(0), pos(p), parentID(-1), depth(0) {}
    int ID;
    CGeoPoint pos;
    int parentID;
    double depth;
    bool checkCollision(const CGeoPoint& p) { return (margin(p) < (0.0)); }
    double margin(const CGeoPoint& p) { return pos.dist(p) - 2 * ROBOT_RADIUS; }
};

class RRTTree {
    public:
        RRTTree() {}
        RRTTree(CGeoPoint p) { rrtVec.push_back(RRTNode(p)); }
        ~RRTTree(){}
        int getSize() { return rrtVec.size(); }
        void addNewNode(RRTNode node) { rrtVec.push_back(node); }
        RRTNode getNode(int ID) { return rrtVec[ID]; }
        int getNearestNodeID(const CGeoPoint& p);
        void clearTree() { rrtVec.clear(); }
        vector<RRTNode> rrtVec;
};

class RRTPlanner
{
public:
    RRTPlanner(CGeoPoint start, CGeoPoint goal, vector<Obstacle> obs) : start_(start),
        goal_(goal), rrtTree(start), obsVec(obs) {
        setNearestNode(start);
    }
    bool findRRTPath(vector<CGeoPoint>& trajVec);

    bool generateRandNode(RRTNode& q_rand);
    bool addNewNode2RRT(RRTNode& q_rand);
    bool checkNode2Goal(RRTNode& node);
    bool checkCollision(const CGeoPoint& p);
    bool pointCheck(RRTNode& m, RRTNode& n);

    void setStart(const CGeoPoint& s) { start_.pos = s; }
    void setGoal(const CGeoPoint& g) { goal_.pos = g; }
    void setNearestNode(const CGeoPoint& p) { nearestGoal.pos = p; dist2Goal = goal_.pos.dist(p); }
    RRTNode getStart() { return start_; }
    RRTNode getGoal() { return goal_; }
    vector<int> getPath(int end_id);
private:
    RRTTree rrtTree;
    vector<Obstacle> obsVec;
    RRTNode start_, goal_, nearestGoal;
    double dist2Goal;
};

#endif // RRTPLANNER_H

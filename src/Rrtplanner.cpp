#include "RRTplanner.h"
#include <QDebug>
#include <ctime>

int RRTTree::getNearestNodeID(const CGeoPoint& p) {
    int index = 0;
    double length = rrtVec[0].pos.dist(p);
    for (size_t i = 0; i < rrtVec.size(); i++) {
        if (rrtVec[i].pos.dist(p) < length) {
            length = rrtVec[i].pos.dist(p);
            index = i;
        }
    }
    return index;
}

bool RRTPlanner::findRRTPath(vector<CGeoPoint>& trajVec) {
    vector<CGeoPoint>().swap(trajVec);
    RRTNode qRand;
    vector<int> rrtPath;
    srand((unsigned)time(NULL));
    static int i = 0;
    while(true)
    {
        bool randNodeSuccess = false, addNewNodeSuccess = false, toGoalSuccess = false;

        randNodeSuccess = generateRandNode(qRand);

        if(randNodeSuccess) {
            addNewNodeSuccess = addNewNode2RRT(qRand);
        }

        //if succeed adding a new node
        if(addNewNodeSuccess) {
            toGoalSuccess = checkNode2Goal(nearestGoal);
        }

        // if get the goal
        if(toGoalSuccess) {
            //add goal
            goal_.ID = rrtTree.getSize();
            goal_.parentID = nearestGoal.ID;
            goal_.depth = nearestGoal.depth + goal_.pos.dist(nearestGoal.pos);
            rrtTree.addNewNode(goal_);
            rrtPath = getPath(rrtTree.getSize() - 1);
            break;
        }
    }

    for(size_t i = 0; i < rrtPath.size(); i++) {
        CGeoPoint tempPos = rrtTree.rrtVec[rrtPath[i]].pos;
        trajVec.push_back(tempPos);
    }

    return true;
}

bool RRTPlanner::generateRandNode(RRTNode& qRand) {
    int q = rand() % 100;
    if (q < GOAL_RATE) {
        qRand = goal_;
        return true;
    }
    else {
        qRand.pos = CGeoPoint(rand() % WIDTH, rand() % HEIGHT);
    }
    return !checkCollision(qRand.pos);
}

bool RRTPlanner::addNewNode2RRT(RRTNode& qRand) {
    RRTNode qNear, qNew;
    //find the nearest_nodes in rrt_tree
    int qNearID = rrtTree.getNearestNodeID(qRand.pos);
    qNear = rrtTree.getNode(qNearID);

    //expand a rrtStepSize to get the new Node
    CVector deltaL = qRand.pos - qNear.pos;
    CVector theta = deltaL / deltaL.mod();
    qNew.pos = qNear.pos + theta * RRT_STEP_SIZE;

    //to check if there is any obstacle between q_near and q_new
    if(!pointCheck(qNear, qNew)) {
        double cost = qNear.depth + RRT_STEP_SIZE;
        int parentID = qNear.ID;
        for(int i = 0; i < rrtTree.getSize(); i++) {
            if(qNew.pos.dist(rrtTree.rrtVec[i].pos) < RADIUS) {
                double tempCost = (rrtTree.rrtVec[i].depth + qNew.pos.dist(rrtTree.rrtVec[i].pos));
                if(tempCost < cost) {
                  cost =  tempCost;
                  parentID = i;
                }
            }
        }

        qNew.parentID = parentID;
        qNew.depth = cost;
        qNew.ID = rrtTree.getSize();

        for(int i = 0; i < rrtTree.getSize(); i++) {
            if(qNew.pos.dist(rrtTree.rrtVec[i].pos) < RADIUS) {
                double cost = (qNew.depth + rrtTree.rrtVec[i].pos.dist(qNew.pos));
                if(cost < rrtTree.rrtVec[i].depth) {
                    rrtTree.rrtVec[i].depth = cost;
                    rrtTree.rrtVec[i].parentID = qNew.ID;
                }
            }
        }
        rrtTree.addNewNode(qNew);

        //calculate the distance from q_new to goal
        double distance = qNew.pos.dist(goal_.pos);
        if (distance < dist2Goal) {
            nearestGoal = qNew;
            dist2Goal = distance;
        }
        return true;
    }
    else
        return false;
}

bool RRTPlanner::checkNode2Goal(RRTNode &node) {
    double margin = goal_.pos.dist(node.pos) - ROBOT_RADIUS;
    return margin < ACCEPT_RADIUS;
}

bool RRTPlanner::checkCollision(const CGeoPoint& p) {
    //check if the new node is in the obs
    for(size_t i = 0; i < obsVec.size(); i++) {
        if(obsVec[i].checkPoint(p)) return true;
    }
    return false;
}

bool RRTPlanner::pointCheck(RRTNode& m, RRTNode& n) {
    for (size_t i = 0; i < obsVec.size(); i++) {
        if (obsVec[i].checkSegment(m.pos, n.pos)) return true;
    }
    return false;
}

vector<int> RRTPlanner::getPath(int end_id) {
    vector<int> path;
    path.push_back(end_id); //push goal to path
    RRTNode init = rrtTree.getNode(end_id), temp = init;
    // init is the fixed node, temp is the moving node
    while(temp.ID != 0) {
        //back optimization
        while (temp.ID != 0 && !pointCheck(init, rrtTree.getNode(temp.parentID))) {
            temp = rrtTree.getNode(temp.parentID);
        }
        path.insert(path.begin(), temp.ID);
        init = temp;
        if (temp.ID != 0)
            temp = rrtTree.getNode(temp.parentID);
        else break;
    }
    return path;
}

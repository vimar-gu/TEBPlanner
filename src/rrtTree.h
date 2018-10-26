#ifndef RRTTREE_H
#define RRTTREE_H

#include <iostream>
#include <vector>
#include "Model.h"
#include "config.h"

using namespace std;

class rrtTree
{
    public:
        struct rrtNode
        {
            int ID;
            CGeoPoint pos;
            int parentID;
            double depth;
            bool checkCollision(const CGeoPoint& p)
            {
                // float margin = pos.dist(p) - 2*robot_radius;
                return (margin(p) < (0.0));
            }
            double margin(const CGeoPoint& p)
            {
                return pos.dist(p) - 2*ROBOT_RADIUS;
            }
        };
        rrtTree() {}
        //give the start
        rrtTree(const CGeoPoint& p);
        ~rrtTree(){}
        //get the size of rrtTree
        int getSize();
        //add a new node to rrtTree
        void addNewNode(rrtNode node);
        //get the node whose ID is ID
        rrtNode getNode(int ID);
        //get the nearest node ID to
        int getNearestNodeID(const CGeoPoint& p);
        //
//        vector<int> getPath(int end_id);
        void clearTree();
        vector<rrtNode> rrt_tree;
};
#endif // RRTTREE_H

#include "rrtTree.h"

rrtTree::rrtTree(const CGeoPoint& p)
{
    rrtNode start;
    start.pos = p;
    start.ID = 0;
    start.parentID = -1;
    start.depth = 0;
    rrt_tree.push_back(start);
//    cout << "rrt_tree.size = " << rrt_tree.size() << endl;

}
rrtTree::rrtNode rrtTree::getNode(int ID)
{
    return rrt_tree[ID];
}
int rrtTree::getNearestNodeID(const CGeoPoint& p)
{
    int index = 0;
    double length = rrt_tree[0].pos.dist(p);

    for(int i = 1; i < rrt_tree.size(); i++)
    {
        float tmp = rrt_tree[i].pos.dist(p);
        if ( tmp < length)
        {
            length = tmp;
            index = i;
        }
    }
    return index;
}
void rrtTree::addNewNode(rrtTree::rrtNode node)
{
    rrt_tree.push_back(node);
}
//vector<int> rrtTree::getPath(int end_id)
//{
//    vector<int> path;
//    path.push_back(end_id);
//    while(rrt_tree[path.front()].ID != 0)
//    {
//        while()
//        path.insert(path.begin(), rrt_tree[path.front()].parentID);
//    }
//    return path;
//}
int rrtTree::getSize()
{
    return rrt_tree.size();
}
void rrtTree::clearTree()
{
    rrt_tree.clear();
}

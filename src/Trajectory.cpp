#include "Trajectory.h"
#include "Tebplanner.h"

using namespace std;

void Trajectory::clearTraj() {
    vector<State*>().swap(trajVec);
}

void Trajectory::findPath(const CGeoPoint& s, const CGeoPoint& g, vector<Obstacle> o)
{
    clearTraj();
    rrtTree tmpRRT(s);
    srand((unsigned)time(NULL));
//    cout << "start = " << s.x() << " " << s.y() << endl;
    rrtTree::rrtNode q_rand;
    setStart(s);
    setGoal(g);
    setNearestNode(s);
    my_rrt = tmpRRT;
    vector<int> rrt_path;
    bool addNewNodeSuccess = false, toGoalSuccess = false, randNodeSuccess = false;
    obs = o;
    int num = 0;
    while(true)
    {
        randNodeSuccess = generateRandNode(q_rand);
        if(randNodeSuccess);
        {
            addNewNodeSuccess = addNewNode2RRT(q_rand);
            //if succeed adding a new node
            if(addNewNodeSuccess)
            {
                toGoalSuccess = checkNode2Goal(nearest_goal);
                // if get the goal
                if(toGoalSuccess)
                {
                    //add goal to
//                    cout << "toGoalSuccess" << endl;
                    goal.ID = my_rrt.getSize();
                    goal.parentID = nearest_goal.ID;
                    goal.depth = nearest_goal.depth + goal.pos.dist(nearest_goal.pos);
                    my_rrt.addNewNode(goal);
                    cout << "my_rrt.Size = "<< my_rrt.getSize() << endl;
                    rrt_path = getPath(my_rrt.getSize()-1);
                    break;
                }
            }
        }
        num = num + 1;
    }
    for(int i = 0; i < rrt_path.size(); i++)
    {
        State* temp_state = new State(my_rrt.rrt_tree[rrt_path[i]].pos);
        trajVec.push_back(temp_state);
    }
}

/**
 * @brief Trajectory::generateRandNode
 * @param q_rand
 * @return fasle if q_rand is not on the obstacles
 */
bool Trajectory::generateRandNode(rrtTree::rrtNode& q_rand)
{
    int q = rand() % 100;
    if (q < GOAL_RATE)
    {
        q_rand = goal;
        return true;
    }
    else
    {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        CGeoPoint pos(x, y);
        q_rand.pos = pos;
    }
    if(checkCollision(q_rand.pos))
    {
        return false;
    }
    else return true;
}

/**
 * @brief Trajectory::plan
 * @param start : the start point
 * @param end : the goal point
 * @param obs : the obstacles on the map
 */
void Trajectory::plan(State start, State end, vector<Obstacle> obs) {
    clearTraj();
    CVector start2End = end.pos() - start.pos();
    CVector length = start2End / (TRAJ_POINT_NUMBER + 1);
    for (int i = 1; i <= TRAJ_POINT_NUMBER; i++) {
        State* tempState = new State(start.pos() + length * i);
        trajVec.push_back(tempState);
    }
//    TEBPlanner tebPlanner(trajVec, start, end, obs);
}

State* Trajectory::getFirstState() {
    return trajVec[0];
}

/**
 * @brief Trajectory::setStart
 * @param s
 */
void Trajectory::setStart(const CGeoPoint& s)
{
    start.pos = s;
}
/**
 * @brief Trajectory::setGoal
 * @param g
 */
void Trajectory::setGoal(const CGeoPoint& g)
{
    goal.pos = g;
}
void Trajectory::setNearestNode(const CGeoPoint& p)
{
    nearest_goal.pos = p;
    distance_to_goal = goal.pos.dist(p);
}
/**
 * @brief Trajectory::getStart
 * @return start point
 */
rrtTree::rrtNode Trajectory::getStart()
{
    return start;
}
/**
 * @brief Trajectory::getGoal
 * @return goal point
 */
rrtTree::rrtNode Trajectory::getGoal()
{
    return goal;
}

/**
 * @brief Trajectory::addNewNode2RRT
 * @param q_rand
 * @param last_node: the node which is closet to the goal
 * @return
 */
bool Trajectory::addNewNode2RRT(rrtTree::rrtNode& q_rand)
{
    rrtTree::rrtNode q_near, q_new;
    //find the nearest_nodes in rrt_tree
    int q_nearID = my_rrt.getNearestNodeID(q_rand.pos);
    q_near = my_rrt.getNode(q_nearID);


    //expand a rrtStepSize to get the new Node
    CVector deltaL = q_rand.pos - q_near.pos;
    CVector theta = deltaL / deltaL.mod();
    q_new.pos = q_near.pos + theta * rrtStepSize;
    //to check if there is any obstacle between q_near and q_new
    if(pointCheck(q_near, q_new))
    {
        double cost = q_near.depth + rrtStepSize;
        int parentID = q_near.ID;
        for(int i = 0; i < my_rrt.getSize(); i++)
        {
            if(q_new.pos.dist(my_rrt.rrt_tree[i].pos) < RADIUS)
            {

                double temp_cost = (my_rrt.rrt_tree[i].depth + q_new.pos.dist(my_rrt.rrt_tree[i].pos));
                if(temp_cost < cost)
                {
                  cost =  temp_cost;
                  parentID = i;
                }
            }
        }

        q_new.parentID = parentID;
        q_new.depth = cost;
        q_new.ID = my_rrt.getSize();

        for(int i = 0; i < my_rrt.getSize(); i++)
        {
            if(q_new.pos.dist(my_rrt.rrt_tree[i].pos) < RADIUS)
            {
                double cost = (q_new.depth + my_rrt.rrt_tree[i].pos.dist(q_new.pos));
                if(cost < my_rrt.rrt_tree[i].depth)
                {
                    my_rrt.rrt_tree[i].depth = cost;
                    my_rrt.rrt_tree[i].parentID = q_new.ID;
                }
            }
        }
        my_rrt.addNewNode(q_new);
        //calculate the distance from q_new to goal
        double distance = q_new.pos.dist(goal.pos);
        if (distance < distance_to_goal)
        {
            nearest_goal = q_new;
            distance_to_goal = distance;
        }
        return true;
    }
    else
        return false;
}

bool Trajectory::checkNode2Goal(rrtTree::rrtNode &node)
{
    double margin = goal.pos.dist(node.pos) - ROBOT_RADIUS;
    if(margin < acceptRadius)
    {
        return true;
    }
    else return false;
}

bool Trajectory::checkCollision(const CGeoPoint& p)
{
    bool index = false;
    //check if the new node is in the obs
    for(int i = 0; i < obs.size(); i++)
    {
        if(obs[i].checkCollision(p))
        {
            index = true;
            break;
        }
    }

    return index;
}
/**
 * @brief Trajectory::pointCheck
 * @param m
 * @param n
 * @return true if there is no obstacle between m and n
 */
bool Trajectory::pointCheck(rrtTree::rrtNode& m, rrtTree::rrtNode& n)
{
    double p = 0;
    CVector deltaL = n.pos - m.pos;
    CGeoPoint temp_point;

    while(p <= 1)
    {
        temp_point = m.pos + deltaL * p;
        if(checkCollision(temp_point))
        {
            return false;
        }
        p += 0.2;
    }
    return true;
}
vector<int> Trajectory::getPath(int end_id)
{
    vector<int> path;
    path.push_back(end_id); //push goal to path
    rrtTree::rrtNode init = my_rrt.getNode(end_id), temp = init;
    // init is the fixed node, temp is the moving node
    while(temp.ID != 0)
    {
        //回溯优化路径
        while (temp.ID != 0 && pointCheck(init, my_rrt.getNode(temp.parentID)))
        {
            temp = my_rrt.getNode(temp.parentID);
        }
        path.insert(path.begin(), temp.ID);
        init = temp;
        if (temp.ID != 0)
            temp = my_rrt.getNode(temp.parentID);
        else break;
    }
    start.pos.print();
    my_rrt.getNode(path.front()).pos.print();
    return path;
}
//vector<int> Trajectory::getPath(int end_id)
//{
//    vector<int> path;
//    path.push_back(end_id);
//    while(my_rrt.rrt_tree[path.front()].ID != 0)
//    {
//        path.insert(path.begin(), my_rrt.rrt_tree[path.front()].parentID);
//    }
//    return path;
//}
void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}




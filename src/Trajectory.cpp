#include "Trajectory.h"

using namespace std;

// 清除trajVec并最小化它的容量，可以理解为交换技巧的变体
void Trajectory::clearTraj() {
    vector<State>().swap(trajVec);
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
                    rrt_path = my_rrt.getPath(my_rrt.getSize()-1);
                    break;
                }
            }
        }
        num = num + 1;
    }
    for(int i = 0; i < rrt_path.size(); i++)
    {
        State temp_state(my_rrt.rrt_tree[rrt_path[i]].pos);
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
void Trajectory::plan(CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    clearTraj();
    CVector start2End = end - start;
    CVector length = start2End / (TRAJ_POINT_NUMBER + 1);
    for (int i = 1; i <= TRAJ_POINT_NUMBER; i++) {
        State tempState(start + length * i);
        trajVec.push_back(tempState);
    }
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
    q_new.parentID = q_nearID;

    //to check if there is any obstacle between q_near and q_new
    if(pointCheck(q_near, q_new))
    {
        q_new.ID = my_rrt.getSize();
        q_new.depth = q_near.depth + rrtStepSize;
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

void Trajectory::setTrajectoryMethod(int method) {
    trajMethod = method ? TEB : RRT;
}




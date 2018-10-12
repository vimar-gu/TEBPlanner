#ifndef CONFIG_H
#define CONFIG_H

// the parameters for trajectory algorithm

//const int ROBOT_NUMBER = 1; // the number of our robots
//const int OBSTACLE_NUMBER = 10; // the number of obstacles
//const int TRAJ_POINT_NUMBER = 10; // the origin number of trajectory points
//const double ORIGIN_X = 0; // the x offset
//const double ORIGIN_Y = 0; // the y offset
//const double OBSTACLE_RADIUS = 10; // the size of obstacles .. wait to be modified to various ones
//const double ROBOT_RADIUS = 10;

#define ROBOT_NUMBER 1
#define OBSTACLE_NUMBER  10
#define TRAJ_POINT_NUMBER  10
#define ORIGIN_X  0
#define ORIGIN_Y  0
#define OBSTACLE_RADIUS  10
#define ROBOT_RADIUS  10
#define WIDTH  720
#define HEIGHT  720
#define rrtStepSize 10
#define acceptRadius 5
#define GOAL_RATE 50

#endif // CONFIG_H

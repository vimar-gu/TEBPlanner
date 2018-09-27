#ifndef CONFIG_H
#define CONFIG_H

// the const parameters for the TEB algorithm

const int ROBOT_NUMBER = 1; // the number of our robots
const int OBSTACLE_NUMBER = 10; // the number of obstacles
const int TRAJ_POINT_NUMBER = 10; // the number of origin trajectory points
const int MAX_ITERATION_TIMES = 10; // the max number of iteration times for optimization
const double ORIGIN_X = 100; // the offset for init
const double ORIGIN_Y = 100; // the offset for init
const double OBSTACLE_RADIUS = 10; // the size of obstacles .. wait to be modified to various ones

#endif // CONFIG_H

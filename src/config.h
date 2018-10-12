#ifndef CONFIG_H
#define CONFIG_H

// #define WIDTH  720
// #define HEIGHT  720
// #define rrtStepSize 10
// #define acceptRadius 5
// #define GOAL_RATE 50

// the const parameters for field painting

extern int ROBOT_NUMBER; // the number of our robots
extern int OBSTACLE_NUMBER; // the number of obstacles
extern double ORIGIN_X; // the offset for init
extern double ORIGIN_Y; // the offset for init
extern double OBSTACLE_RADIUS; // the size of obstacles .. wait to be modified to various ones
extern double PI;
extern double FRAME_NUMBER;

// the const parameters for trajectory planning

extern int TRAJ_POINT_NUMBER; // the number of origin trajectory points
extern int MAX_ITERATION_TIMES; // the max number of iteration times for optimization

// the const parameters of robot moving constraints

extern double MAX_VELOCITY;
extern double MAX_ACCELERATION;
extern double MAX_ROTATION_VELOCITY;
extern double MAX_ROTATION_ACCELERATION;

// the const parameters for obstacle avoiding

extern double MIN_OBSTACLE_DISTANCE;

#endif // CONFIG_H

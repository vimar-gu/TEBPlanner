#ifndef CONFIG_H
#define CONFIG_H

// the const parameters for field painting

const int ROBOT_NUMBER = 1; // the number of our robots
const int OBSTACLE_NUMBER = 2; // the number of obstacles
const double ORIGIN_X = 100; // the offset for init
const double ORIGIN_Y = 100; // the offset for init
const double OBSTACLE_RADIUS = 10; // the size of obstacles .. wait to be modified to various ones
const double PI = 3.14159265358979323846;
const double FRAME_NUMBER = 60;

// the const parameters for trajectory planning

const int TRAJ_POINT_NUMBER = 10; // the number of origin trajectory points
const int MAX_ITERATION_TIMES = 10; // the max number of iteration times for optimization

// the const parameters of robot moving constraints

const double MAX_VELOCITY = 1000;
const double MAX_ACCELERATION = 1000;
const double MAX_ROTATION_VELOCITY = 15;
const double MAX_ROTATION_ACCELERATION = 15;

// the const parameters for obstacle avoiding

const double MIN_OBSTACLE_DISTANCE = 100;

#endif // CONFIG_H

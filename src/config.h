#ifndef CONFIG_H
#define CONFIG_H

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
extern int OUTER_ITERATION_TIMES; // the iteration times for outer loops
extern int INNER_ITERATION_TIMES; // the iteration times for inner optimization
extern double MAX_END_FORCE; // the max force for the end trajectory pos
extern double ALPHA; // origin learining rate
extern double BETA_1; // the weight for last frame
extern double BETA_2;
extern double EPSILON; // the little value avoiding gradient explosion

// the const parameters of robot moving constraints
extern double MAX_VELOCITY;
extern double MAX_ACCELERATION;
extern double MAX_ROTATION_VELOCITY;
extern double MAX_ROTATION_ACCELERATION;

// the const parameters for obstacle avoiding

extern double MIN_OBSTACLE_DISTANCE;

#endif // CONFIG_H

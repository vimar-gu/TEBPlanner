#ifndef CONFIG_H
#define CONFIG_H

namespace Config {

    // the const parameters for field painting

    namespace FieldConfig {
        extern int ROBOT_NUMBER; // the number of our robots
        extern int OBSTACLE_NUMBER; // the number of obstacles
        extern int TRAJ_POINT_NUMBER; // the origin number of trajectory points
        extern double ORIGIN_X; // the x offset
        extern double ORIGIN_Y; // the y offset
        extern double OBSTACLE_RADIUS; // the size of obstacles .. wait to be modified to various ones
    }

    // the const parameters for trajectory planning

    namespace TrajectoryConfig {
        extern int TRAJ_POINT_NUMBER; // the number of origin trajectory points
        extern int MAX_ITERATION_TIMES; // the max number of iteration times for optimization
    }

    // the const parameters of robot moving constraints

    namespace RobotConfig {
        extern double MAX_VELOCITY;
        extern double MAX_ACCELERATION;
        extern double MAX_ROTATION_VELOCITY;
        extern double MAX_ROTATION_ACCELERATION;
    }

    // the const parameters for obstacle avoiding

    namespace ObstacleConfig {
        extern double MIN_OBSTACLE_DISTANCE;
    }
}

#endif // CONFIG_H

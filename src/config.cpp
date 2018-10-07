#include "config.h"

namespace Config {

    // field config

    namespace FieldConfig {
        int ROBOT_NUMBER = 1;
        int OBSTACLE_NUMBER = 10;
        int TRAJ_POINT_NUMBER = 10;
        double ORIGIN_X = 100;
        double ORIGIN_Y = 100;
        double OBSTACLE_RADIUS = 10;
    }

    // trajectory config

    namespace TrajectoryConfig {
        int TRAJ_POINT_NUMBER = 10;
        int MAX_ITERATION_TIMES = 10;
    }

    // robot config

    namespace RobotConfig {
        double MAX_VELOCITY = 1000;
        double MAX_ACCELERATION = 1000;
        double MAX_ROTATION_VELOCITY = 15;
        double MAX_ROTATION_ACCELERATION = 15;
    }

    // obstacle config

    namespace ObstacleConfig {
        double MIN_OBSTACLE_DISTANCE = 100;
    }
}

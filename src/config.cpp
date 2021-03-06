﻿#include "config.h"

// field config

int ROBOT_NUMBER = 1;
int OBSTACLE_NUMBER = 2;
double ORIGIN_X = 100;
double ORIGIN_Y = 100;
double OBSTACLE_RADIUS = 10;
double PI = 3.14159265358979323846;
double FRAME_NUMBER = 5;

// trajectory config

int TRAJ_POINT_NUMBER = 10;
int OUTER_ITERATION_TIMES = 5;
int INNER_ITERATION_TIMES = 5;
double MAX_END_FORCE = 100;
double ALPHA = 1;
double BETA_1 = 0.5;
double BETA_2 = 0.5;
double EPSILON = 0.01;

// robot config

double MAX_VELOCITY = 1000;
double MAX_ACCELERATION = 1000;
double MAX_ROTATION_VELOCITY = 15;
double MAX_ROTATION_ACCELERATION = 15;

// obstacle config

double MIN_OBSTACLE_DISTANCE = 100;

//jiangchao

int WIDTH = 720;
int HEIGHT = 720;
int RRT_STEP_SIZE = 10;
int ACCEPT_RADIUS = 1;
int GOAL_RATE = 50;
int ROBOT_RADIUS = 10;
int RADIUS  = 50;

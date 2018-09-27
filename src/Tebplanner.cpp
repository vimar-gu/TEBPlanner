#include "Tebplanner.h"

TEBPlanner::TEBPlanner() {

}

TEBPlanner::TEBPlanner(vector<CGeoPoint> &trajVec, CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    plan(trajVec, start, end, obs);
}

void TEBPlanner::plan(vector<CGeoPoint> &trajVec, CGeoPoint start, CGeoPoint end, vector<Obstacle> obs) {
    int index = 0;
    while (index < MAX_ITERATION_TIMES) {
        for (int i = 0; i < trajVec.size(); i++) {
            if (i == 0) { // the first point

            }
            else if (i == trajVec.size() - 1) { // the final point

            }
            else { // normal points

            }
        }
    }
}

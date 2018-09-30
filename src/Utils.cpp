#include "Utils.h"
#include "config.h"

double normalize(double x) {
    while (x > PI) {
        x -= PI * 2;
    }
    while (x < -PI) {
        x += PI * 2;
    }
    return x;
}

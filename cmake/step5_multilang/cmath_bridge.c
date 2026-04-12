#include "cmath_bridge.h"
#include <math.h>

/* Newton-Raphson square root (20 iterations) */
double fast_sqrt(double x) {
    if (x < 0.0) return -1.0;
    double guess = x / 2.0;
    for (int i = 0; i < 20; i++)
        guess = (guess + x / guess) / 2.0;
    return guess;
}

double fast_log2(double x) {
    return log(x) / log(2.0);
}

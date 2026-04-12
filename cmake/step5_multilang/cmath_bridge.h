#ifndef CMATH_BRIDGE_H
#define CMATH_BRIDGE_H

#ifdef __cplusplus
extern "C" {  /* tell the C++ linker these symbols use C calling convention */
#endif

double fast_sqrt(double x);
double fast_log2(double x);

#ifdef __cplusplus
}
#endif

#endif

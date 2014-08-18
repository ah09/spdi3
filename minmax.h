#ifndef MINMAX_H_INCLUDED
#define MINMAX_H_INCLUDED
#include <stdio.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MAX(a, b) ((a) > (b) ? (a) : (b))


/* min finds the lowest of four doubles */
inline double min(double, double, double, double);

/* max finds the highest of four doubles */
inline double max(double, double, double, double);


#endif

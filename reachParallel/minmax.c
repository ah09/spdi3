#include "minmax.h"


inline double min(double a, double b, double c, double d) {
    return MIN(a, MIN(b, MIN(c, d)));
}

inline double max(double a, double b, double c, double d) {
    return MAX(a, MAX(b, MAX(c, d)));
}

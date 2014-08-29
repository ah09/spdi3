#include "basicStructures.h"
#include "det.h"


inline double detVector(vector v, line e) {
    return (v.y*(e.pt1.x - e.pt2.x)) - (v.x*(e.pt1.y - e.pt2.y));
}

inline double detLine(line l1, line l2) {
    double A1 = l1.pt2.y - l1.pt1.y;
    double A2 = l2.pt2.y - l2.pt1.y;
    double B1 = l1.pt1.x - l1.pt2.x;
    double B2 = l2.pt1.x - l2.pt2.x;
    double d = A1*B2 - A2*B1;
    return d;
}

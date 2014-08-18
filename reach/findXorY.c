#include "basicStructures.h"
#include "findXorY.h"


inline double findX(double y, line l) {
    double D = l.pt1.x - l.pt2.x;
    double E = l.pt2.y - l.pt1.y;
    return l.pt1.x + (D / E) * (l.pt1.y - y);
}

inline double findY(double x, line l) {
    double D = l.pt1.x - l.pt2.x;
    double E = l.pt2.y - l.pt1.y;
    return (E / D)*(l.pt1.x - x) + l.pt1.y;
}

#include "basicStructures.h"
#include "lineIntersection.h"


point lineIntersection(line l1, line l2){
    point p;
    double A1 = l1.pt2.y - l1.pt1.y;
    double A2 = l2.pt2.y - l2.pt1.y;
    double B1 = l1.pt1.x - l1.pt2.x;
    double B2 = l2.pt1.x - l2.pt2.x;
    double C1 = A1*l1.pt1.x + B1*l1.pt1.y;
    double C2 = A2*l2.pt1.x + B2*l2.pt1.y;
    double d = A1*B2 - A2*B1;
    if (d != 0){
        p.x = ((B2*C1 - B1*C2) / d);
        p.y = ((A1*C2 - A2*C1) / d);
        return p;
    }
    else {
        return pointNotFound;
    }
}

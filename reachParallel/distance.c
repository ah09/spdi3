#include <math.h>
#include "basicStructures.h"
#include "distance.h"


double distance(point p1, point p2){
    double d = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
    return d;
}

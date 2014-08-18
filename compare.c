#include <stdbool.h>
#include "basicStructures.h"
#include "compare.h"


bool samePointAs(point a, point b) {
    if (a.x == b.x && a.y == b.y) {return true;}
    return false;
}

bool sameLineAs(line a, line b) {
    if (samePointAs(a.pt1, b.pt1) && samePointAs(a.pt2, b.pt2)) {return true;}
    return false;
}

bool sameRegionAs(region a, region b) {
    if (sameLineAs(a.e.e1, b.e.e1) && sameLineAs(a.e.e2, b.e.e2) && sameLineAs(a.e.e3, b.e.e3) && sameLineAs(a.e.e4, b.e.e4)){return true;}
    return false;
}

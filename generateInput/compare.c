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

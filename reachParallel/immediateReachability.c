#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "det.h"
#include "immediateReachability.h"
#include "intervalRange.h"
#include "minmax.h"


line immediateReachability(line I, vector a, vector b, line e) {
    double da = detVector(a, e);
    double db = detVector(b, e);
    if (da == 0 && db == 0) {return lineNotFound;}
    line ir = intervalRange(I, a, b, e);
    //printf("ir is (%f, %f) to (%f, %f)\n", ir.pt1.x, ir.pt1.y, ir.pt2.x, ir.pt2.y);
    //printf("e is (%f, %f) to (%f, %f)\n", e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);
    if ((a.x > 0 && b.x > 0 && MAX(ir.pt1.x, ir.pt2.x) <= MIN(I.pt1.x, I.pt2.x))
        || (a.x < 0 && b.x < 0 && MIN(ir.pt1.x, ir.pt2.x) >= MAX(I.pt1.x, I.pt2.x))
        || (a.y > 0 && b.y > 0 && MAX(ir.pt1.y, ir.pt2.y) <= MIN(I.pt1.y, I.pt2.y))
        || (a.y < 0 && b.y < 0 && MIN(ir.pt1.y, ir.pt2.y) >= MAX(I.pt1.y, I.pt2.y))) {
    return lineNotFound;
    }
    if (isCollinear(I, e) || ir.pt1.x > e.pt2.x || ir.pt2.x < e.pt1.x
        || (ir.pt1.x == ir.pt2.x && (ir.pt1.y > e.pt2.y || ir.pt2.y < e.pt1.y))) {
        return lineNotFound;
    }
    else{
        line r = collinearIntersection(ir, e);
        if (r.pt1.x == r.pt2.x && r.pt1.y == r.pt2.y) {return lineNotFound;}
        else {return r;}
    }
}

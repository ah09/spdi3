#include <math.h>
#include "basicStructures.h"
#include "det.h"
#include "minmax.h"
#include "findXorY.h"
#include "intervalRange.h"


point intersection(point I, vector v, line e) {
    double d = det(v, e);
    double ex = e.pt1.x - e.pt2.x;
    double ey = e.pt2.y - e.pt1.y;
    double Iv = v.y*I.x - v.x*I.y;
    double exy = ey*e.pt1.x + ex*e.pt1.y;
    if (d != 0) {
        double x = (ex*Iv + v.x*exy) / d;
        double y = (v.y*exy - ey*Iv) / d;
        point p = {x, y};
        return p;
    }
    point p = { INFINITY, INFINITY };
    return p;
}

line intervalRange(line I, vector a, vector b, line e) {
    point i1a = intersection(I.pt1, a, e);
    point i1b = intersection(I.pt1, b, e);
    point i2a = intersection(I.pt2, a, e);
    point i2b = intersection(I.pt2, b, e);
    double xmin = min(i1a.x, i1b.x, i2a.x, i2b.x);
    double ymin = min(i1a.y, i1b.y, i2a.y, i2b.y);
    if (i1a.x == INFINITY) {
        i1a.x = -INFINITY;
        i1a.y = -INFINITY;
    }
    if (i1b.x == INFINITY) {
        i1b.x = -INFINITY;
        i1b.y = -INFINITY;
    }
    if (i2a.x == INFINITY) {
        i2a.x = -INFINITY;
        i2a.y = -INFINITY;
    }
    if (i2b.x == INFINITY) {
        i2b.x = -INFINITY;
        i2b.y = -INFINITY;
    }
    double xmax = max(i1a.x, i1b.x, i2a.x, i2b.x);
    double ymax = max(i1a.y, i1b.y, i2a.y, i2b.y);
    line l;
    if (xmin < xmax) {
        l.pt1.x = xmin;
        l.pt1.y = findY(xmin, e);
        l.pt2.x = xmax;
        l.pt2.y = findY(xmax, e);
        return l;
    }
    l.pt1.x = findX(ymin, e);
    l.pt1.y = ymin;
    l.pt2.x = findX(ymax, e);
    l.pt2.y = ymax;
    return l;
}

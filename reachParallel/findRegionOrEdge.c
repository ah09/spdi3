#include <math.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "minmax.h"


line hasEdgeWithLineSegment(region R, line l){
    if (isContainedIn(l, R.e.e1)) {return R.e.e1;}
    if (isContainedIn(l, R.e.e2)) {return R.e.e2;}
    if (isContainedIn(l, R.e.e3)) {return R.e.e3;}
    if (isContainedIn(l, R.e.e4)) {return R.e.e4;}
    return lineNotFound;
}

line findEdgeWithLineSegment(region s[], int size, line l){
    int i;
    for (i = 0; i < size; ++i){
        line e = hasEdgeWithLineSegment(s[i], l);
        if (e.pt1.x != -1){
            return e;
        }
    }
    return lineNotFound;
}

bool hasEdge(region R, line e) {
    if (sameLineAs(R.e.e1, e)) {return true;}
    else if (sameLineAs(R.e.e2, e)) {return true;}
    else if (sameLineAs(R.e.e3, e)) {return true;}
    else if (sameLineAs(R.e.e4, e)) {return true;}
    else {return false;}
}

bool hasEntryEdge(region R, line e) {
    if (!hasEdge(R, e)) {return false;}
    point edgeMiddle;
    edgeMiddle.x = (e.pt2.x + e.pt1.x) / 2;
    edgeMiddle.y = (e.pt1.y + e.pt2.y) / 2;
    point regionMiddle;
    double xmax = MAX(max(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), max(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    double xmin = MIN(min(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), min(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    regionMiddle.x = (xmax + xmin) / 2;
    double ymax = MAX(max(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), max(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    double ymin = MIN(min(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), min(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    regionMiddle.y = (ymax + ymin) / 2;
    vector edgeToMiddle;
    edgeToMiddle.x = regionMiddle.x - edgeMiddle.x;
    edgeToMiddle.y = regionMiddle.y - edgeMiddle.y;
    double aScalarProduct = edgeToMiddle.x*R.v.a.x + edgeToMiddle.y*R.v.a.y;
    double bScalarProduct = edgeToMiddle.x*R.v.b.x + edgeToMiddle.y*R.v.b.y;
    double edgeToMiddleMagnitude = sqrt(edgeToMiddle.x*edgeToMiddle.x + edgeToMiddle.y*edgeToMiddle.y);
    double aMagnitude = sqrt(R.v.a.x*R.v.a.x + R.v.a.y*R.v.a.y);
    double bMagnitude = sqrt(R.v.b.x*R.v.b.x + R.v.b.y*R.v.b.y);
    double aVectorAngle = aScalarProduct / (edgeToMiddleMagnitude*aMagnitude);
    double bVectorAngle = bScalarProduct / (edgeToMiddleMagnitude*bMagnitude);
    if (aVectorAngle > 0 || bVectorAngle > 0) {return true;}
    return false;
}

region findRegionWithEntryEdge(region s[], int size, line e) {
    int i;
    for (i = 0; i < size; ++i){
        if (hasEntryEdge(s[i], e)){
            return s[i];
        }
    }
    return regionNotFound;
}

/*int numberOfReachableEdges(line I, region R) {
    if (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1
        && immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1
        && immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1
        && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1){
        return 4;
    }
    if ((immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt2.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1)){
        return 3;
    }
    if ((immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1)
        || (immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1 && immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1)){
        return 2;
    }
    if (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1 || immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1
        ||immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1|| immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1){
        return 1;
    }
    return -1;
}*/

int numberOfReachableEdges(line I, region R) {
    int i = 0;
    if (immediateReachability(I, R.v.a, R.v.b, R.e.e1).pt1.x != -1) {++i;}
    if (immediateReachability(I, R.v.a, R.v.b, R.e.e2).pt1.x != -1) {++i;}
    if (immediateReachability(I, R.v.a, R.v.b, R.e.e3).pt1.x != -1) {++i;}
    if (immediateReachability(I, R.v.a, R.v.b, R.e.e4).pt1.x != -1) {++i;}
    return i;
}

bool hasExitEdge(region R, line e) {
    if (!hasEdge(R, e)){return false;}
    point edgeMiddle;
    edgeMiddle.x = (e.pt2.x + e.pt1.x) / 2;
    edgeMiddle.y = (e.pt1.y + e.pt2.y) / 2;
    point regionMiddle;
    double xmax = MAX(max(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), max(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    double xmin = MIN(min(R.e.e1.pt1.x, R.e.e2.pt1.x, R.e.e3.pt1.x, R.e.e4.pt1.x), min(R.e.e1.pt2.x, R.e.e2.pt2.x, R.e.e3.pt2.x, R.e.e4.pt2.x));
    regionMiddle.x = (xmax + xmin) / 2;
    double ymax = MAX(max(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), max(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    double ymin = MIN(min(R.e.e1.pt1.y, R.e.e2.pt1.y, R.e.e3.pt1.y, R.e.e4.pt1.y), min(R.e.e1.pt2.y, R.e.e2.pt2.y, R.e.e3.pt2.y, R.e.e4.pt2.y));
    regionMiddle.y = (ymax + ymin) / 2;
    vector edgeToMiddle;
    edgeToMiddle.x = regionMiddle.x - edgeMiddle.x;
    edgeToMiddle.y = regionMiddle.y - edgeMiddle.y;
    double aScalarProduct = edgeToMiddle.x*R.v.a.x + edgeToMiddle.y*R.v.a.y;
    double bScalarProduct = edgeToMiddle.x*R.v.b.x + edgeToMiddle.y*R.v.b.y;
    double edgeToMiddleMagnitude = sqrt(edgeToMiddle.x*edgeToMiddle.x + edgeToMiddle.y*edgeToMiddle.y);
    double aMagnitude = sqrt(R.v.a.x*R.v.a.x + R.v.a.y*R.v.a.y);
    double bMagnitude = sqrt(R.v.b.x*R.v.b.x + R.v.b.y*R.v.b.y);
    double aVectorAngle = aScalarProduct / (edgeToMiddleMagnitude*aMagnitude);
    double bVectorAngle = bScalarProduct / (edgeToMiddleMagnitude*bMagnitude);
    if (aVectorAngle < 0 || bVectorAngle < 0) {return true;}
    return false;
}

region findRegionWithExitEdge(region s[], int size, line e) {
    int i;
    for (i = 0; i < size; ++i){
        if (hasExitEdge(s[i], e)){
            return s[i];
        }
    }
    return regionNotFound;
}

line findEdgeInRegionWithSameX(region R, double x) {
    if (R.e.e1.pt1.x == x && R.e.e1.pt2.x == x){return R.e.e1;}
    else if (R.e.e2.pt1.x == x && R.e.e2.pt2.x == x){return R.e.e2;}
    else if (R.e.e3.pt1.x == x && R.e.e3.pt2.x == x){return R.e.e3;}
    else if (R.e.e4.pt1.x == x && R.e.e4.pt2.x == x){return R.e.e4;}
    else {return lineNotFound;}
}

line findEdgeInRegionWithSameY(region R, double y) {
    if (R.e.e1.pt1.y == y && R.e.e1.pt2.y == y){return R.e.e1;}
    else if (R.e.e2.pt1.y == y && R.e.e2.pt2.y == y){return R.e.e2;}
    else if (R.e.e3.pt1.y == y && R.e.e3.pt2.y == y){return R.e.e3;}
    else if (R.e.e4.pt1.y == y && R.e.e4.pt2.y == y){return R.e.e4;}
    else {return lineNotFound;}
}

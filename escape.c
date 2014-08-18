#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "cycle.h"
#include "distance.h"
#include "escape.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "sort.h"


int findLineSubsetInArray(line array[], int num_elements, line element){
    int i;
    for (i = 0; i < num_elements; ++i){
        if (isSomeCollinearIntersection(element, array[i])) {return i;}
    }
    return -1;
}

line limit(int i, struct node* thisNode, int sizeOfCycle) {
    line thisEdge = findNode(thisNode, thisNode->i - sizeOfCycle + i + 1)->edge;
    line x1 = findNode(thisNode, thisNode->i - 3 * sizeOfCycle + i + 1)->interval;
    line x2 = findNode(thisNode, thisNode->i - 2 * sizeOfCycle + i + 1)->interval;
    line x3 = findNode(thisNode, thisNode->i - sizeOfCycle + i + 1)->interval;
    double u1 = distance(x1.pt1, x2.pt1);
    double u2 = distance(x2.pt1, x3.pt1);
    double d1 = distance(x1.pt2, x2.pt2);
    double d2 = distance(x2.pt2, x3.pt2);
    double ur;
    if (u2 == 0) {ur = 0;}
    else {ur = u2 / u1;}
    double dr;
    if (d2 == 0) {dr = 0;}
    else {dr = d2 / d1;}
    line x;
    if (ur < 1) {
        if (thisEdge.pt1.x == thisEdge.pt2.x) {
            x.pt1.x = x1.pt1.x;
            x.pt1.y = x1.pt1.y + (u1 / (1 - ur));
        }
        else {
            x.pt1.x = x1.pt1.x + (u1 / (1 - ur));
            x.pt1.y = x1.pt1.y;
        }
    }
    else {
        if (thisEdge.pt1.x == thisEdge.pt2.x) {
            x.pt1.x = thisEdge.pt1.x;
            x.pt1.y = thisEdge.pt1.y - 0.1;
        }
        else {
            x.pt1.x = thisEdge.pt1.x - 0.1;
            x.pt1.y = thisEdge.pt1.y;
        }
    }
    if (dr < 1) {
        if (thisEdge.pt1.x == thisEdge.pt2.x) {
            x.pt2.x = x1.pt2.x;
            x.pt2.y = x1.pt2.y + (d1 / (1 - dr));
        }
        else {
            x.pt2.x = x1.pt2.x + (d1 / (1 - dr));
            x.pt2.y = x1.pt2.y;
        }
    }
    else {
        if (thisEdge.pt1.x == thisEdge.pt2.x) {
            x.pt2.x = thisEdge.pt2.x;
            x.pt2.y = thisEdge.pt2.y + 0.1;
        }
        else {
            x.pt2.x = thisEdge.pt2.x + 0.1;
            x.pt2.y = thisEdge.pt2.y;
        }
    }
    return x;
}

bool isLimitWithinEdge(int i, struct node* thisNode, int sizeOfCycle) {
    line l = limit(i, thisNode, sizeOfCycle);
    if (lineSetMinusLine(l, findNode(thisNode, thisNode->i - sizeOfCycle + i + 1)->edge).pt1.x != -1) {return false;}
    else {return true;}
}

#include <stdlib.h>
#include <stdbool.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "cycle.h"
#include "draw.h"
#include "escape.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "reach.h"


int inescapableInt = 0;

void deallocate(struct node* thisNode) {
    if (thisNode == NULL) return;
    struct node* lastNode = thisNode->previous;
    if (thisNode->split != 2) {
        printf("deallocating node[%d]: (%f, %f) to (%f, %f)\n", thisNode->i, thisNode->interval.pt1.x, thisNode->interval.pt1.y, thisNode->interval.pt2.x, thisNode->interval.pt2.y);
        thisNode = NULL;
        free(thisNode);
        deallocate(lastNode);
    }
    else {
        thisNode->split = 1;
    }
}

line reach (region s[], int size, struct node* lastNode, line e) {
    lastNode->edge = findEdgeWithLineSegment(s, size, lastNode->interval);
    //line inescapable[4 * size];
    //int inescapableInt = 0;
    //if (draw == true) {printf("say so\n");}
    if (inescapableInt > 0) {
        int inescapableInterval = findLineSubsetInArray(inescapable, inescapableInt, lastNode->interval);
        if (inescapableInterval != -1) {
            line newInterval = lineSetMinusLine(lastNode->interval, inescapable[inescapableInterval]);
            if (newInterval.pt1.x == -1) {
                return newInterval;
            }
            lastNode->interval = newInterval;
        }
    }
    int sizeOfCycle = patternDetection(lastNode);
    if (sizeOfCycle != -1) {
        bool escapable = false;
        //int i = lastNode->i - 3 * sizeOfCycle + 1;
        //int finish = i + sizeOfCycle;
        int i = 0;
        //while (i < finish) {
        while (i < sizeOfCycle) {
            line foundEdge = findNode(lastNode, i)->edge;
            region R = findRegionWithExitEdge(s, size, foundEdge);
            if (!isLimitWithinEdge(i, lastNode, sizeOfCycle)) {
                line sameY1 = findEdgeInRegionWithSameY(R, foundEdge.pt1.y + 0.1);
                line sameY2 = findEdgeInRegionWithSameY(R, foundEdge.pt2.y - 0.1);
                line sameX1 = findEdgeInRegionWithSameX(R, foundEdge.pt1.x + 0.1);
                line sameX2 = findEdgeInRegionWithSameX(R, foundEdge.pt2.x - 0.1);
                if (foundEdge.pt1.x == foundEdge.pt2.x
                    && findRegionWithEntryEdge(s, size, sameY1).e.e1.pt1.x != -1
                    && findRegionWithEntryEdge(s, size, sameY2).e.e1.pt1.x != -1
                    && !sameLineAs(sameY1, e) && !sameLineAs(sameY2, e)) {
                    escapable = true;
                    break; // escape
                }
                else if (foundEdge.pt1.y == foundEdge.pt2.y
                    && findRegionWithEntryEdge(s, size, sameX1).e.e1.pt1.x != -1
                    && findRegionWithEntryEdge(s, size, sameX2).e.e1.pt1.x != -1
                    && !sameLineAs(sameX1, e) && !sameLineAs(sameX2, e)) {
                    escapable = true;
                    break; // escape
                }
            }
            ++i;
            /*if (escapable == false) {
                int count = inescapableInt;
                for (count = inescapableInt; count < inescapableInt + sizeOfCycle; ++count) {
                    inescapable[count] = findNode(lastNode, count + inescapableInt)->interval;
                }
                inescapableInt = inescapableInt + sizeOfCycle; // records the loop
                return lineNotFound; // stuck in loop
            }*/
        }
        //if (escapable == false) {return lineNotFound;}
        if (escapable == false) {
            int count = inescapableInt;
            for (count = inescapableInt; count < inescapableInt + sizeOfCycle; ++count) {
                inescapable[count] = findNode(lastNode, count + inescapableInt)->interval;
            }
            inescapableInt = inescapableInt + sizeOfCycle; // records the loop
            return lineNotFound; // stuck in loop
        }
    }
    region R = findRegionWithEntryEdge(s, size, lastNode->edge);
    if (R.e.e1.pt1.x != -1) {
        if (hasEdge(R, e)) {
            line l = immediateReachability(lastNode->interval, R.v.a, R.v.b, e);
            if (l.pt1.x != -1) {
                if (draw == true) {addInterval(lastNode->interval, l);}
                return l;
            }
        }
        lastNode->split = numberOfReachableEdges(lastNode->interval, R);
        line l1 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e1);
        if (l1.pt1.x != -1) {
            struct node* thisNode = NULL;
            thisNode = malloc(sizeof(struct node));
            thisNode->i = lastNode->i + 1;
            thisNode->split = 0;
            thisNode->interval = l1;
            thisNode->previous = lastNode;
            if (draw) {addInterval(lastNode->interval, thisNode->interval);}
            line l = reach(s, size, thisNode, e);
            free(thisNode);
            if (l.pt1.x != -1) {return l;}
        }
        line l2 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e2);
        if (l2.pt1.x != -1) {
            struct node* thisNode = NULL;
            thisNode = malloc(sizeof(struct node));
            thisNode->i = lastNode->i + 1;
            thisNode->split = 0;
            thisNode->interval = l2;
            thisNode->previous = lastNode;
            if (draw) {addInterval(lastNode->interval, thisNode->interval);}
            line l = reach(s, size, thisNode, e);
            free(thisNode);
            if (l.pt1.x != -1) {return l;}
        }
        line l3 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e3);
        if (l3.pt1.x != -1) {
            struct node* thisNode = NULL;
            thisNode = malloc(sizeof(struct node));
            thisNode->i = lastNode->i + 1;
            thisNode->split = 0;
            thisNode->interval = l3;
            thisNode->previous = lastNode;
            if (draw) {addInterval(lastNode->interval, thisNode->interval);}
            line l = reach(s, size, thisNode, e);
            free(thisNode);
            if (l.pt1.x != -1) {return l;}
        }
        line l4 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e4);
        if (l4.pt1.x != -1) {
            struct node* thisNode = NULL;
            thisNode = malloc(sizeof(struct node));
            thisNode->i = lastNode->i + 1;
            thisNode->split = 0;
            thisNode->interval = l4;
            thisNode->previous = lastNode;
            if (draw) {addInterval(lastNode->interval, thisNode->interval);}
            line l = reach(s, size, thisNode, e);
            free(thisNode);
            if (l.pt1.x != -1) {return l;}
        }
    }
    return lineNotFound;
}

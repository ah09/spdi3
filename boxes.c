#include <stdlib.h>
#include <stdio.h>
#include <bool.h>
#include <math.h>
#include "basicStructures.h"
#include "collinearIntersection.h"
#include "compare.h"
#include "cycle.h"
#include "det.h"
#include "escape.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "intervalRange.h"
#include "minmax.h"
#include "reachability.h"
#include "sort.h"
#include "C4SNet.h"


void *init(void *hnd, int size, c4snet_data_t *SPDI, c4snet_data_t *I, c4snet_data_t *e) {
    region s[size];
    int i;
    for (i = 0; i < size; ++i) {
        //printf("size is %d\n", size);
        //printf("i is %d\n", i);
        double *a = C4SNetGetData(SPDI);
        region R = {{{{a[(20*i)],a[(20*i)+1]},{a[(20*i)+2],a[(20*i)+3]}},{{a[(20*i)+4],a[(20*i)+5]},{a[(20*i)+6],a[(20*i)+7]}},{{a[(20*i)+8],a[(20*i)+9]},{a[(20*i)+10],a[(20*i)+11]}},{{a[(20*i)+12],a[(20*i)+13]},{a[(20*i)+14],a[(20*i)+15]}}},{{a[(20*i)+16],a[(20*i)+17]},{a[(20*i)+18],a[(20*i)+19]}}};
        s[i] = R;
    }
    double *a = C4SNetGetData(I);
    struct line start = {{a[0],a[1]},{a[2],a[3]}};
    sort(&start.pt1.x, &start.pt1.y, &start.pt2.x, &start.pt2.y);
    double *b = C4SNetGetData(e);
    struct line* target = malloc(sizeof(struct line));
    target->pt1.x = b[0];
    target->pt1.y = b[1];
    target->pt2.x = b[2];
    target->pt2.y = b[3];
    sort(&target->pt1.x, &target->pt1.y, &target->pt2.x, &target->pt2.y);
    struct node* initial = NULL; 
    initial = malloc(sizeof(struct node));
    initial->i = 0;
    initial->split = 0;
    initial->interval = start;
    initial->previous = NULL;
    //printf("I initial of (%f, %f) to (%f, %f) is at %p\n", initial->interval.pt1.x, initial->interval.pt1.y, initial->interval.pt2.x, initial->interval.pt2.y, initial);
    int B = 0;
    int C = 0;
    C4SNetOut(hnd, 1, size, C4SNetCreate(CTYPE_char, sizeof(struct region) * size, s), C4SNetCreate(CTYPE_char, sizeof(void*), &initial), C4SNetCreate(CTYPE_char, sizeof(void*), &target), B, C);
    int found = 0;
    C4SNetOut(hnd, 2, found);
    return hnd;
}

line inescapable[1000];
int inescapableInt = 0;

void *reachability(void *hnd, int size, c4snet_data_t *a, c4snet_data_t *b, c4snet_data_t *c, int B, int C, int found) {
    struct region *SPDI = (struct region *) C4SNetGetData(a);
    struct node *lastNode = *((struct node **) C4SNetGetData(b));
    struct line *target = *((struct line **) C4SNetGetData(c));
    //const struct line* target = targetPointer;
    //printf("R target of (%f, %f) to (%f, %f) is at %p\n", target->pt1.x, target->pt1.y, target->pt2.x, target->pt2.y, target);
    //printf("R current node[%d] of (%f, %f) to (%f, %f) is at %p\n", lastNode->i, lastNode->interval.pt1.x, lastNode->interval.pt1.y, lastNode->interval.pt2.x, lastNode->interval.pt2.y, lastNode);
    lastNode->edge = findEdgeWithLineSegment(SPDI, size, lastNode->interval);
    if (inescapableInt > 0) {
        int inescapableInterval = findLineSubsetInArray(inescapable, inescapableInt, lastNode->interval);
        if (inescapableInterval != -1) {
            line newInterval = lineSetMinusLine(lastNode->interval, inescapable[inescapableInterval]);
            if (newInterval.pt1.x == -1) {
                printf("in an inescapable loop\n");
                struct node* thisNode = NULL;
                thisNode = malloc(sizeof(struct node));
                thisNode->i = lastNode->i + 1;
                thisNode->split = 0;
                thisNode->interval = lastNode->interval;
                thisNode->previous = lastNode;
                C = 1;
                C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
            }
            else {lastNode->interval = newInterval;}
        }
    }
    struct region R = findRegionWithEntryEdge(SPDI, size, lastNode->edge);
    int sizeOfCycle = patternDetection(lastNode);
    if (sizeOfCycle != -1) {
        bool escapable = false;
        int i = 0;
        while (i < sizeOfCycle) {
            line foundEdge = findNode(lastNode, i)->edge;
            region R = findRegionWithExitEdge(SPDI, size, foundEdge);
            if (!isLimitWithinEdge(i, lastNode, sizeOfCycle)) {
                line sameY1 = findEdgeInRegionWithSameY(R, foundEdge.pt1.y + 0.1);
                line sameY2 = findEdgeInRegionWithSameY(R, foundEdge.pt2.y - 0.1);
                line sameX1 = findEdgeInRegionWithSameX(R, foundEdge.pt1.x + 0.1);
                line sameX2 = findEdgeInRegionWithSameX(R, foundEdge.pt2.x - 0.1);
                if (foundEdge.pt1.x == foundEdge.pt2.x
                    && findRegionWithEntryEdge(SPDI, size, sameY1).e.e1.pt1.x != -1
                    && findRegionWithEntryEdge(SPDI, size, sameY2).e.e1.pt1.x != -1
                    && !sameLineAs(sameY1, *target) && !sameLineAs(sameY2, *target)) {
                    escapable = true;
                    break; // escape
                }
                else if (foundEdge.pt1.y == foundEdge.pt2.y
                    && findRegionWithEntryEdge(SPDI, size, sameX1).e.e1.pt1.x != -1
                    && findRegionWithEntryEdge(SPDI, size, sameX2).e.e1.pt1.x != -1
                    && !sameLineAs(sameX1, *target) && !sameLineAs(sameX2, *target)) {
                    escapable = true;
                    break; // escape
                }
            }
            ++i;
        }
        if (escapable == false) {
            printf("in an inescapable loop\n");
            int count = inescapableInt;
            for (count = inescapableInt; count < inescapableInt + sizeOfCycle; ++count) {
                inescapable[count] = findNode(lastNode, count + inescapableInt)->interval;
                printf("inescapable[%d] is (%f, %f) to (%f, %f)\n", count, findNode(lastNode, count + inescapableInt)->interval.pt1.x, findNode(lastNode, count + inescapableInt)->interval.pt1.y, findNode(lastNode, count + inescapableInt)->interval.pt2.x, findNode(lastNode, count + inescapableInt)->interval.pt2.y);
            }
            inescapableInt = inescapableInt + sizeOfCycle; // records the loop
            struct node* thisNode = NULL;
            thisNode = malloc(sizeof(struct node));
            thisNode->i = lastNode->i + 1;
            thisNode->split = 0;
            thisNode->interval = lastNode->interval;
            thisNode->previous = lastNode;
            C = 1;
            C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
        }
    }
    else if (R.e.e1.pt1.x != -1 && found == 0) {
        struct line possibleFind = immediateReachability(lastNode->interval, R.v.a, R.v.b, *target);
        if (hasEdge(R, *target) && possibleFind.pt1.x != -1) {
            printf("found at (%f, %f) to (%f, %f)\n", possibleFind.pt1.x, possibleFind.pt1.y, possibleFind.pt2.x, possibleFind.pt2.y);
            found = 1;
            C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &lastNode), c, B, C, found);
                /*struct line* l = NULL;
                l = malloc(sizeof(struct line));
                l->pt1.x = temp.pt1.x;
                l->pt1.y = temp.pt1.y;
                l->pt2.x = temp.pt2.x;
                l->pt2.y = temp.pt2.y;
                printf("l is (%f, %f) to (%f, %f)\n", l->pt1.x, l->pt1.y, l->pt2.x, l->pt2.y);
                C4SNetOut(hnd, 2, C4SNetCreate(CTYPE_char, sizeof(void*), &l));*/
            //C4SNetOut(hnd, 2, C4SNetCreate(CTYPE_char, sizeof(void*), &temp));
        }

        else {
            //lastNode->split = numberOfReachableEdges(lastNode->interval, R);
            //printf("number of reachable edges is %d\n", lastNode->split);
            line l1 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e1);
            if (l1.pt1.x != -1) {
                lastNode->split = lastNode->split + 1;
                struct node* thisNode = NULL;
                thisNode = malloc(sizeof(struct node));
                thisNode->i = lastNode->i + 1;
                thisNode->split = 0;
                thisNode->interval = l1;
                thisNode->previous = lastNode;
                C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
            }
            line l2 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e2);
            if (l2.pt1.x != -1) {
                lastNode->split = lastNode->split + 1;
                struct node* thisNode = NULL;
                thisNode = malloc(sizeof(struct node));
                thisNode->i = lastNode->i + 1;
                thisNode->split = 0;
                thisNode->interval = l2;
                thisNode->previous = lastNode;
                C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
            }
            line l3 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e3);
            if (l3.pt1.x != -1) {
                lastNode->split = lastNode->split + 1;
                struct node* thisNode = NULL;
                thisNode = malloc(sizeof(struct node));
                thisNode->i = lastNode->i + 1;
                thisNode->split = 0;
                thisNode->interval = l3;
                thisNode->previous = lastNode;
                C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
                //printf("R1 node[%d] of (%f, %f) to (%f, %f) is at %p,\n   node[%d] of (%f, %f) to (%f, %f) is at %p\n", thisNode->i, thisNode->interval.pt1.x, thisNode->interval.pt1.y, thisNode->interval.pt2.x, thisNode->interval.pt2.y, thisNode, lastNode->i, lastNode->interval.pt1.x, lastNode->interval.pt1.y, lastNode->interval.pt2.x, lastNode->interval.pt2.y, lastNode);
            }
            line l4 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e4);
            if (l4.pt1.x != -1) {
                lastNode->split = lastNode->split + 1;
                struct node* thisNode = NULL;
                thisNode = malloc(sizeof(struct node));
                thisNode->i = lastNode->i + 1;
                thisNode->split = 0;
                thisNode->interval = l4;
                thisNode->previous = lastNode;
                C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
                //printf("R1 node[%d] of (%f, %f) to (%f, %f) is at %p,\n   node[%d] of (%f, %f) to (%f, %f) is at %p\n", thisNode->i, thisNode->interval.pt1.x, thisNode->interval.pt1.y, thisNode->interval.pt2.x, thisNode->interval.pt2.y, thisNode, lastNode->i, lastNode->interval.pt1.x, lastNode->interval.pt1.y, lastNode->interval.pt2.x, lastNode->interval.pt2.y, lastNode);
                //free(thisNode);
                //if (l.pt1.x != -1) {return l;}
            }
        printf("the number of reachable edges from (%f, %f) to (%f, %f) is %d\n", lastNode->interval.pt1.x, lastNode->interval.pt1.y, lastNode->interval.pt2.x, lastNode->interval.pt2.y, lastNode->split);
        }
    }
    else {
        struct node* thisNode = NULL;
        thisNode = malloc(sizeof(struct node));
        thisNode->i = lastNode->i + 1;
        thisNode->split = 0;
        thisNode->interval = lastNode->interval;
        thisNode->previous = lastNode;
        B = 1;
        C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode), c, B, C, found);
        //printf("R2 node[%d] of (%f, %f) to (%f, %f) is at %p,\n   node[%d] of (%f, %f) to (%f, %f) is at %p\n", thisNode->i, thisNode->interval.pt1.x, thisNode->interval.pt1.y, thisNode->interval.pt2.x, thisNode->interval.pt2.y, thisNode, lastNode->i, lastNode->interval.pt1.x, lastNode->interval.pt1.y, lastNode->interval.pt2.x, lastNode->interval.pt2.y, lastNode);
    }
    //printf("deallocate from lastNode[%d]\n", lastNode->i);
    //deallocate(lastNode);
    //printf("found is %d\n", found);
    return hnd;
}

void *deallocate(void *hnd, int size, c4snet_data_t *a, c4snet_data_t *b, c4snet_data_t *c, int B, int C, int found) {
    //struct region *SPDI = (struct region *) C4SNetGetData(a);
    struct node *thisNode = *((struct node **) C4SNetGetData(b));
    //struct line *target = *((struct line **) C4SNetGetData(c));
    //static int numberOfTrajectories = 1;
    //const struct line* target = targetPointer;
    static int currentFound = 0;
    if (found == 1 || B == 1 || C == 1) {
        struct line tempInterval = thisNode->interval;
        struct line tempEdge = thisNode->edge;
        //numberOfTrajectories = numberOfTrajectories - 1;
        if (found == 1 && currentFound == 0) {
            currentFound = 1;
            //C4SNetOut(hnd, 2, C4SNetCreate(CTYPE_char, sizeof(void*), &thisNode->interval));
        }
        void deallocation(struct node* thisNode) {
            if (thisNode == NULL) {
		C4SNetFree(a);
		C4SNetFree(b);
    		//free(C4SNetGetData(c));
		C4SNetFree(c);
                if (found == 0) {
                    printf("unreachable\n");
                }
                else {
                    printf("reachable at (%f, %f) to (%f, %f) of the edge (%f, %f) to (%f, %f)\n", tempInterval.pt1.x, tempInterval.pt1.y, tempInterval.pt2.x, tempInterval.pt2.y, tempEdge.pt1.x, tempEdge.pt1.y, tempEdge.pt2.x, tempEdge.pt2.y);
                }
            return;
            }
            struct node* lastNode = thisNode->previous;
            if (thisNode->split != 2) {
                printf("deallocating node[%d]: (%f, %f) to (%f, %f)\n", thisNode->i, thisNode->interval.pt1.x, thisNode->interval.pt1.y, thisNode->interval.pt2.x, thisNode->interval.pt2.y);
                thisNode = NULL;
                free(thisNode);
                deallocation(lastNode);
            }
            else {
                thisNode->split = 1;
            }
        }
        deallocation(thisNode);
    }
    else {
        C4SNetOut(hnd, 1, size, a, C4SNetCreate(CTYPE_char, sizeof(struct node), &thisNode), c, B, C);
        C4SNetOut(hnd, 2, found);
    }
    return hnd;
}

void *presentResult(void *hnd, c4snet_data_t *a) {
    //struct line l = *(struct line *) C4SNetGetData(a);
    struct line *l = *((struct line **) C4SNetGetData(a));
    printf("reachable from (%f, %f) to (%f, %f)\n", l->pt1.x, l->pt1.y, l->pt2.x, l->pt2.y);
    //C4SNetOut(hnd, 1, C4SNetCreate(CTYPE_char, sizeof(struct line), &l));
    C4SNetOut(hnd, 1, 0);
    return hnd;
}

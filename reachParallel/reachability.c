#include <stdlib.h>
#include "basicStructures.h"
#include "findRegionOrEdge.h"
#include "immediateReachability.h"
#include "reachability.h"


/*void deallocate(struct node* thisNode) {
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
}*/

line reaching(region s[], int size, struct node* lastNode, line e) {
    printf("interval[%d] is (%f, %f) to (%f, %f)\n", lastNode->i, lastNode->interval.pt1.x, lastNode->interval.pt1.y, lastNode->interval.pt2.x, lastNode->interval.pt2.y);
    lastNode->edge = findEdgeWithLineSegment(s, size, lastNode->interval);
    printf("edge[%d] is (%f, %f) to (%f, %f)\n", lastNode->i, lastNode->edge.pt1.x, lastNode->edge.pt1.y, lastNode->edge.pt2.x, lastNode->edge.pt2.y);
    region R = findRegionWithEntryEdge(s, size, lastNode->edge);
    if (R.e.e1.pt1.x != -1) {
        if (hasEdge(R, e)) {
            line l = immediateReachability(lastNode->interval, R.v.a, R.v.b, e);
            if (l.pt1.x != -1) {
                //deallocate(lastNode);
                return l;
            }
        }
        lastNode->split = numberOfReachableEdges(lastNode->interval, R);
        printf("number of reachable edges is %d\n", lastNode->split);
        line l1 = immediateReachability(lastNode->interval, R.v.a, R.v.b, R.e.e1);
        if (l1.pt1.x != -1) {
            struct node* thisNode = NULL;
            thisNode = malloc(sizeof(struct node));
            thisNode->i = lastNode->i + 1;
            thisNode->split = 0;
            thisNode->interval = l1;
            thisNode->previous = lastNode;
            line l = reaching(s, size, thisNode, e);
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
            line l = reaching(s, size, thisNode, e);
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
            line l = reaching(s, size, thisNode, e);
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
            line l = reaching(s, size, thisNode, e);
            free(thisNode);
            if (l.pt1.x != -1) {return l;}
        }
    }
    //printf("deallocate from lastNode[%d]\n", lastNode->i);
    //deallocate(lastNode);
    return lineNotFound;
}

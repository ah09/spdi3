#include <stdbool.h>
#include "basicStructures.h"
#include "compare.h"
#include "cycle.h"


struct node* findNode(struct node* thisNode, int i) {
    struct node* lastNode = NULL;
    if (i <= thisNode->i) {
        lastNode = thisNode;
        while (lastNode != NULL) {
            if (lastNode->i == i) {
                return lastNode;
            }
            lastNode = lastNode->previous;
        }
    }
    return lastNode;
}

int patternDetection(struct node* thisNode) {
    int sizeOfCycle = -1;
    int size = thisNode->i + 1;
    line thisEdge = thisNode->edge;
    struct node* lastNode = thisNode->previous;
    while (lastNode != NULL) {
        if (sameLineAs(lastNode->edge, thisEdge) && size >= 3*(size-lastNode->i-1)) {
            line cycle[size - lastNode->i - 1];
            int j;
            for (j = 0; j < size-lastNode->i-1; ++j) {
                cycle[j] = findNode(thisNode, lastNode->i + j + 1)->edge;
            }
            for (j = 0; j < size-lastNode->i-1; ++j) {
                int node2 = 2*(lastNode->i+1)-size+j;
                line foundEdge2 = findNode(thisNode, node2)->edge;
                int node3 = 3*(lastNode->i+1)-2*size+j;
                line foundEdge3 = findNode(thisNode, node3)->edge;
                if (!sameLineAs(cycle[j], foundEdge2) || !sameLineAs(cycle[j], foundEdge3)) {return -1;}
            }
            sizeOfCycle = size-lastNode->i-1;
            break;
        }
        lastNode = lastNode -> previous;
    }
    return sizeOfCycle;
}

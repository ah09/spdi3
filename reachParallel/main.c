#include <stdio.h>
#include <stdlib.h>
#include "basicStructures.h"
#include "reach.h"

int main()
{
    region R1;
    regionEdges re1 = { {{1, 1}, {2, 1}}, {{1, 1}, {1, 2}}, {{1, 2}, {2, 2}}, {{2, 1}, {2, 2}} };
    regionVectors rv1 = { {1, 0.5}, {1, 0.5} };
    R1.e = re1;
    R1.v = rv1;
    region R2;
    regionEdges re2 = { {{2, 1}, {3, 1}}, {{2, 1}, {2, 2}}, {{2, 2}, {3, 2}}, {{3, 1}, {3, 2}} };
    regionVectors rv2 = { {1, 0}, {1, 0} };
    R2.e = re2;
    R2.v = rv2;
    region R3;
    regionEdges re3 = { {{1, 2}, {2, 2}}, {{1, 2}, {1, 3}}, {{1, 3}, {2, 3}}, {{2, 2}, {2, 3}} };
    regionVectors rv3 = { {0, 1}, {0, 1} };
    R3.e = re3;
    R3.v = rv3;
    region SPDI[3] = {R1, R2, R3};
    int size = sizeof(SPDI) / sizeof(SPDI[0]);

    line start = {{1, 1.25}, {1, 1.75}};
    struct node* initial = NULL;
    initial = malloc(sizeof(struct node));
    initial->i = 0;
    initial->split = 0;
    initial->interval = start;
    initial->previous = NULL;

    line target = {{3, 1}, {3, 2}};
    line l = reach(SPDI, size, initial, target);
    if (l.pt1.x != -1) {
        printf("l is (%f, %f) to (%f, %f)\n", l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y);
    }
    else {printf("can't be reached\n");}
    free(initial);

    return 0;
}

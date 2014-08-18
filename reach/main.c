#include <stdio.h>
#include <stdlib.h>
#include "basicStructures.h"
#include "reach.h"

int main()
{
    /*region R1;
    regionEdges re1 = { {{1, 1}, {2, 1}}, {{1, 1}, {1, 2}}, {{1, 2}, {2, 2}}, {{2, 1}, {2, 2}} };
    regionVectors rv1 = { {1, -1}, {1, -1} };
    R1.e = re1;
    R1.v = rv1;
    region R2;
    regionEdges re2 = { {{2, 1}, {3, 1}}, {{2, 1}, {2, 2}}, {{2, 2}, {3, 2}}, {{3, 1}, {3, 2}} };
    regionVectors rv2 = { {1, 1}, {1, 1} };
    R2.e = re2;
    R2.v = rv2;
    region R3;
    regionEdges re3 = { {{1, 2}, {2, 2}}, {{1, 2}, {1, 3}}, {{1, 3}, {2, 3}}, {{2, 2}, {2, 3}} };
    regionVectors rv3 = { {-1, -1}, {-1, -1} };
    R3.e = re3;
    R3.v = rv3;
    region R4;
    regionEdges re4 = { {{2, 2}, {3, 2}}, {{2, 2}, {2, 3}}, {{2, 3}, {3, 3}}, {{3, 2}, {3, 3}} };
    regionVectors rv4 = { {-1, 1}, {-1, 1} };
    R4.e = re4;
    R4.v = rv4;
    region SPDI[4];
    SPDI[0] = R1;
    SPDI[1] = R2;
    SPDI[2] = R3;
    SPDI[3] = R4;*/
    region R1;
    regionEdges re1 = { {{1, 1}, {2, 1}}, {{1, 1}, {1, 2}}, {{1, 2}, {2, 2}}, {{2, 1}, {2, 2}} };
    regionVectors rv1 = { {1, -1}, {1, -1} };
    R1.e = re1;
    R1.v = rv1;
    region R2;
    regionEdges re2 = { {{2, 1}, {3, 1}}, {{2, 1}, {2, 2}}, {{2, 2}, {3, 2}}, {{3, 1}, {3, 2}} };
    regionVectors rv2 = { {1, 1}, {1, 0} };
    R2.e = re2;
    R2.v = rv2;
    region R3;
    regionEdges re3 = { {{3, 1}, {4, 1}}, {{3, 1}, {3, 2}}, {{3, 2}, {4, 2}}, {{4, 1}, {4, 2}} };
    regionVectors rv3 = { {1, 1}, {1, 1} };
    R3.e = re3;
    R3.v = rv3;
    region R4;
    regionEdges re4 = { {{1, 2}, {2, 2}}, {{1, 2}, {1, 3}}, {{1, 3}, {2, 3}}, {{2, 2}, {2, 3}} };
    regionVectors rv4 = { {0, -1}, {0, -1} };
    R4.e = re4;
    R4.v = rv4;
    region R5;
    regionEdges re5 = { {{2, 2}, {3, 2}}, {{2, 2}, {2, 3}}, {{2, 3}, {3, 3}}, {{3, 2}, {3, 3}} };
    regionVectors rv5 = { {0, 1}, {0, 1} };
    R5.e = re5;
    R5.v = rv5;
    region R6;
    regionEdges re6 = { {{3, 2}, {4, 2}}, {{3, 2}, {3, 3}}, {{3, 3}, {4, 3}}, {{4, 2}, {4, 3}} };
    regionVectors rv6 = { {0, 1}, {0, 1} };
    R6.e = re6;
    R6.v = rv6;
    region R7;
    regionEdges re7 = { {{1, 3}, {2, 3}}, {{1, 3}, {1, 4}}, {{1, 4}, {2, 4}}, {{2, 3}, {2, 4}} };
    regionVectors rv7 = { {-1, -1}, {-1, -1} };
    R7.e = re7;
    R7.v = rv7;
    region R8;
    regionEdges re8 = { {{2, 3}, {3, 3}}, {{2, 3}, {2, 4}}, {{2, 4}, {3, 4}}, {{3, 3}, {3, 4}} };
    regionVectors rv8 = { {-1, 1}, {-1, 0} };
    R8.e = re8;
    R8.v = rv8;
    region R9;
    regionEdges re9 = { {{3, 3}, {4, 3}}, {{3, 3}, {3, 4}}, {{3, 4}, {4, 4}}, {{4, 3}, {4, 4}} };
    regionVectors rv9 = { {-1, 1}, {-1, 1} };
    R9.e = re9;
    R9.v = rv9;
    region SPDI[9];
    SPDI[0] = R1;
    SPDI[1] = R2;
    SPDI[2] = R3;
    SPDI[3] = R4;
    SPDI[4] = R5;
    SPDI[5] = R6;
    SPDI[6] = R7;
    SPDI[7] = R8;
    SPDI[8] = R9;

    int size = sizeof(SPDI) / sizeof(SPDI[0]);

    line start = {{2, 1.25}, {2, 1.75}};
    struct node* initial = NULL;
    initial = malloc(sizeof(struct node));
    initial->i = 0;
    initial->split = 0;
    initial->interval = start;
    initial->previous = NULL;

    line target = {{2, 2}, {2, 3}};
    line l = reach(SPDI, size, initial, target);
    if (l.pt1.x != -1) {
        printf("l is (%f, %f) to (%f, %f)\n", l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y);
    }
    else {printf("can't be reached\n");}
    free(initial);

    return 0;
}

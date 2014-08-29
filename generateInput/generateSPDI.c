#include "basicStructures.h"
#include "findRegionOrEdge.h"
#include "generateSPDI.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


regionEdges * generateEdges(region *r, int i, int j) {
    line N;
    line S;
    line W;
    line E;
    N.pt1.x = j;
    N.pt1.y = i + 1;
    N.pt2.x = j + 1;
    N.pt2.y = i + 1;
    r->e.e1 = N;
    S.pt1.x = j;
    S.pt1.y = i;
    S.pt2.x = j + 1;
    S.pt2.y = i;
    r->e.e2 = S;
    W.pt1.x = j;
    W.pt1.y = i;
    W.pt2.x = j;
    W.pt2.y = i + 1;
    r->e.e3 = W;
    E.pt1.x = j + 1;
    E.pt1.y = i;
    E.pt2.x = j + 1;
    E.pt2.y = i + 1;
    r->e.e4 = E;
    return &r->e;
}

regionVectors * generateVectors(region *r, region *SPDI, int size) {
    int vectorScale = 10;
    int xBalance = 0;
    int yBalance = 0;
    vector findA() {
        if (findRegionWithExitEdge(SPDI, size, r->e.e1).e.e1.pt1.x != -1) {
            r->v.a.y = (rand() % vectorScale) * (-1);
            yBalance = 1;
        }
        else {r->v.a.y = (rand() % (2 * vectorScale)) - vectorScale;}
        if (findRegionWithExitEdge(SPDI, size, r->e.e2).e.e1.pt1.x != -1) {
            if (yBalance == 1) {
                r->v.a.y = 0;
                yBalance = 0;
            }
            else {
                r->v.a.y = rand() % vectorScale;
                yBalance = 1;
            }
        }
        if (findRegionWithExitEdge(SPDI, size, r->e.e3).e.e1.pt1.x != -1) {
            r->v.a.x = rand() % vectorScale;
            xBalance = 1;
        }
        else {r->v.a.x = (rand() % (2 * vectorScale)) - vectorScale;}
        if (findRegionWithExitEdge(SPDI, size, r->e.e4).e.e1.pt1.x != -1) {
            if (xBalance == 1) {
                r->v.a.x = 0;
                xBalance = 0;
            }
            else {
                r->v.a.x = rand() % vectorScale;
                xBalance = 1;
            }
        }
        if ((r->v.a.x == 0 && r->v.a.y == 0) || (xBalance = 0 && yBalance == 0)) {
            r->v.a = findA();
            return r->v.a;
        }
        return r->v.a;
    }
    r->v.a = findA();
    xBalance = 0;
    yBalance = 0;
    vector findB(vector a) {
        if (findRegionWithExitEdge(SPDI, size, r->e.e1).e.e1.pt1.x != -1) {
            r->v.b.y = (rand() % vectorScale) * (-1);
            yBalance = 1;
        }
        else {r->v.b.y = (rand() % (2 * vectorScale)) - vectorScale;}
        if (findRegionWithExitEdge(SPDI, size, r->e.e2).e.e1.pt1.x != -1) {
            if (yBalance == 1) {
                r->v.b.y = 0;
                yBalance = 0;
            }
            else {
                r->v.b.y = rand() % vectorScale;
                yBalance = 1;
            }
        }
        if (findRegionWithExitEdge(SPDI, size, r->e.e3).e.e1.pt1.x != -1) {
            r->v.b.x = rand() % vectorScale;
            xBalance = 1;
        }
        else {r->v.b.x = (rand() % (2 * vectorScale)) - vectorScale;}
        if (findRegionWithExitEdge(SPDI, size, r->e.e4).e.e1.pt1.x != -1) {
            if (xBalance == 1) {
                r->v.b.x = 0;
                xBalance = 0;
            }
            else {
                r->v.b.x = rand() % vectorScale;
                xBalance = 1;
            }
        }
        if (r->v.a.x * r->v.b.x + r->v.a.y * r->v.b.y < 0 || (r->v.b.x == 0 && r->v.b.y == 0) || (xBalance = 0 && yBalance == 0)) {
            r->v.b = findB(r->v.a);
            return r->v.b;
        }
        return r->v.b;
    }
    r->v.b = findB(r->v.a);
    if (r->v.a.x * r->v.b.y - r->v.a.y * r->v.b.x < 0) {
        vector tmp = r->v.a;
        r->v.a = r->v.b;
        r->v.b = tmp;
    }
    return &r->v;
}

region * generateSPDI(region *SPDI, int width, int height) {
    srand ( time(NULL) );
    int i;
    int j;
    int regionNumber = 0;
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            if (SPDI[regionNumber].v.a.x == 0 && SPDI[regionNumber].v.a.y == 0) {
                SPDI[regionNumber].e = *generateEdges(&SPDI[regionNumber], i, j);
                SPDI[regionNumber].v = *generateVectors(&SPDI[regionNumber], SPDI, regionNumber);
            }
            ++regionNumber;
        }
    }
    return SPDI;
}

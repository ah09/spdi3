#ifndef BASICSTRUCTURES_H_INCLUDED
#define BASICSTRUCTURES_H_INCLUDED
#include <stdio.h>


/* a point is made from a pair of x,y coordinates */
typedef struct point {
    double x;
    double y;
} point;

point pointNotFound;

/* a line is made from a pair of points,
   at this stage it is assumed that all lines are straight */
typedef struct line {
    struct point pt1;
    struct point pt2;
} line;

line lineNotFound;

/* a vector is made from its x and y components */
typedef struct vector {
    double x;
    double y;
} vector;

/* regionEdges are the four edges of a region */
typedef struct regionEdges {
    struct line e1;
    struct line e2;
    struct line e3;
    struct line e4;
} regionEdges;

/* regionVectors are the two vectors of a region */
typedef struct regionVectors {
    struct vector a;
    struct vector b;
} regionVectors;

/* a region is made up from its edges and vectors */
typedef struct region {
    struct regionEdges e;
    struct regionVectors v;
} region;

region regionNotFound;

/* a node is a component of a trajectory expressed as a unit of a
   linked list, i being the number of edges passed since the initiation,
   split being the number of trajectory splits (will be either 1 or 2),
   interval being the part of the edge passed by the trajectory (may be
   the entire edge itself), edge is the edge passed and previous is a
   pointer to the previous node of the trajectory */
struct node {
    int i;
    int split;
    line interval;
    line edge;
    struct node* previous;
};


#endif

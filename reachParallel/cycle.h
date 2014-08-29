#ifndef CYCLE_H_INCLUDED
#define CYCLE_H_INCLUDED
#include <stdio.h>


/* findNode finds a particular node which is or preceeds a given
    node and given a particular value of i*/
struct node* findNode(struct node*, int);

/* patternDetection detects whether there is a pattern in a given edge
   cycle where any particular sequence of edges is repeated three times */
int patternDetection(struct node*);

#endif

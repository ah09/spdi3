#ifndef REACH_H_INCLUDED
#define REACH_H_INCLUDED
#include <stdio.h>


line inescapable[1000];
int inescapableInt;

/* deallocate should deallocate all of the memory devoted to a trajectory
   branch if that branch is found to terminate at a point */
void deallocate(struct node*);

/* earlier reach attemt involving an array and two pointers was too simplistic,
   a truly recursive function that generates branches is needed */
line reach(region [], int, struct node*, line);

#endif

#ifndef REACH_H_INCLUDED
#define REACH_H_INCLUDED
#include <stdio.h>


/* earlier reach attemt involving an array and two pointers was too simplistic,
   a truly recursive function that generates branches is needed */
line reaching(region [], int, struct node*, line);

/* deallocate should deallocate all of the memory devoted to a trajectory
   branch if that branch is found to terminate at a point */
//void deallocate(struct node*);

#endif

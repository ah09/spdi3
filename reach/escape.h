#ifndef ESCAPE_H_INCLUDED
#define ESCAPE_H_INCLUDED
#include <stdio.h>


/* findLineSubsetInArray returns the index number of a line in an
   array of lines which has collinear intersection with a given line */
int findLineSubsetInArray(line [], int, line);

/* limit returns a particular line segment of an invariance kernel
   with the line segment being the limits of a particular edge where
   if a trajectory were to be within that line segment then it will
   be within the invariance kernel and therefore will never leave that
   set. I find this hard to test */
line limit(int, struct node*, int);

/* isLimitWithinRange checks if the limit of a kernel for a particular
   edge lies within that edge, it is equivalent to finding if the kernel
   is inescapable from that edge */

bool isLimitWithinEdge(int, struct node*, int);


#endif

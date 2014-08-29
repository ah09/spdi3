#ifndef INTERVALRANGE_H_INCLUDED
#define INTERVALRANGE_H_INCLUDED
#include <stdio.h>


/* intersection finds a point where a given vector starting
   from a given point intersects with a particular line,
   if there is no intersection then it will return null */
point intersection(point, vector, line);

/* intervalRange finds a range on a projected line of infinite length which
   both satisfies the same linear equation as a given line and also is
   reachable to a trajectory from a given line and a pair of given vectors,
   the projected line is not the same as the edge as it is not bounded by
   any end points, rather the edge is a segment of this line */
line intervalRange(line, vector, vector, line);


#endif

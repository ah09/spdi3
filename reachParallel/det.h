#ifndef DET_H_INCLUDED
#define DET_H_INCLUDED
#include <stdio.h>


/* detVector finds the relation between a given vector and a
   line, this is used to help to find a point of intersection,
   if the result is zero then the two are parallel */
inline double detVector(vector, line);

/* detLine finds the relation between two lines,
   this is used to help to find a point of intersection,
   if the result is zero then the two are parallel */
inline double detLine(line, line);

#endif

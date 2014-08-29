#ifndef FINDXORY_H_INCLUDED
#define FINDXORY_H_INCLUDED
#include <stdio.h>


/* findX takes a given line and y coordinate and returns the corresponding x coordinate,
   this can only work for non-horizontal lines and should not be called otherwise,
   the basic formula used is x = (C - B*y) / A, where A, B and C are doubles*/
inline double findX(double, line);

/* findY takes a given line and x coordinate and returns the corresponding y coordinate,
   this can only work for non-vertical lines and should not be called otherwise,
   the basic formula used is y = (C - A*x) / B, where A, B and C are doubles*/
inline double findY(double, line);


#endif

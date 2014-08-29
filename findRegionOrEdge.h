#ifndef FINDREGIONOREDGE_H_INCLUDED
#define FINDREGIONOREDGE_H_INCLUDED
#include <stdio.h>
#include <stdbool.h>

/* hasEdgeWithLineSegment determines (sort of) whether a region has an edge
   containing a particular line segment, and if it does it returns the edge */
line hasEdgeWithLineSegment(region R, line l);

/* findEdgeWithLineSegment determines (sort of) whether an edge
   exists anywhere in an SPDI containing a particular line
   segment and if it does exist it returns the edge */
line findEdgeWithLineSegment(region [], int, line);

/* hasEdge determines whether a particular region has a particular edge */
bool hasEdge(region, line);

/* hasEntryEdge determines whether a particular region has
   a particular edge as an entry edge to the region */
bool hasEntryEdge(region, line);

/* findRegionWithEntryEdge finds a region which has
   a particular entry edge, if such a region exists */
region findRegionWithEntryEdge(region [], int, line);

/* numberOfReachableEdges finds the number of immediately reachable
   edges of a particular starting interval of a particular region */
int numberOfReachableEdges(line, region);

/* hasExitEdge determines whether a particular region has
   a particular edge as an exit edge to the region */
bool hasExitEdge(region, line);

/* findRegionWithExitEdge finds a region which has
   a particular exit edge, if such a region exists */
region findRegionWithExitEdge(region [], int, line);

/* findEdgeInRegionWithSameX finds an edge given a region
   and a coordinate for the x coordinate of the edge */
line findEdgeInRegionWithSameX(region, double);

/* findEdgeInRegionWithSameY finds an edge given a region
   and a coordinate for the y coordinate of the edge */
line findEdgeInRegionWithSameY(region, double);


#endif

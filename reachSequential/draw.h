#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED
#include <stdio.h>


extern bool draw;

void makeChart(int, int);

void addToChart(region);

void finishChart(line, line);

void addInterval(line, line);

void joinFiles();


#endif

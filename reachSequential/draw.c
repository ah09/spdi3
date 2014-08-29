#include <stdlib.h>
#include <stdbool.h>
#include "basicStructures.h"
#include "draw.h"


int width = 0;
int height = 0;

void makeChart(int numberOfRegionsWide, int numberOfRegionsHigh) {
    FILE * df;
    df = fopen ("chart.txt", "w+");
    fprintf(df, "%d\n", numberOfRegionsWide);
    fprintf(df, "%d\n", numberOfRegionsHigh);
    fclose(df);
}

void addToChart(region R) {
    FILE * df;
    df = fopen ("chart.txt", "a");
    fprintf(df, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n%f %f %f %f\n", R.e.e1.pt1.x, R.e.e1.pt1.y, R.e.e1.pt2.x, R.e.e1.pt2.y, R.e.e2.pt1.x, R.e.e2.pt1.y, R.e.e2.pt2.x, R.e.e2.pt2.y, R.e.e3.pt1.x, R.e.e3.pt1.y, R.e.e3.pt2.x, R.e.e3.pt2.y, R.e.e4.pt1.x, R.e.e4.pt1.y, R.e.e4.pt2.x, R.e.e4.pt2.y, R.v.a.x, R.v.a.y, R.v.b.x, R.v.b.y);
    fclose(df);
}

void finishChart(line initial, line target) {
    FILE * df;
    df = fopen ("chart.txt", "a");
    fprintf(df, "%f %f %f %f\n%f %f %f %f\n", initial.pt1.x, initial.pt1.y, initial.pt2.x, initial.pt2.y, target.pt1.x, target.pt1.y, target.pt2.x, target.pt2.y);
    fclose(df);
}

int numberOfIntervals = 0;

void addInterval(line parent, line child) {
    ++numberOfIntervals;
    if (parent.pt1.x == -1) {
        FILE * df;
        df = fopen ("intervals.txt", "w+");
        fprintf(df, "%d\n", numberOfIntervals);
        fprintf(df, "%f %f %f %f %f %f %f %f\n", child.pt1.x, child.pt1.y, child.pt2.x, child.pt2.y, parent.pt1.x, parent.pt1.y, parent.pt2.x, parent.pt2.y);
        fclose(df);
    }
    else {
        FILE * df;
        df = fopen ("intervals.txt", "r+");
        fprintf(df, "%d\n", numberOfIntervals);
        fclose(df);
        df = fopen("intervals.txt", "a");
        fprintf(df, "%f %f %f %f %f %f %f %f\n", child.pt1.x, child.pt1.y, child.pt2.x, child.pt2.y, parent.pt1.x, parent.pt1.y, parent.pt2.x, parent.pt2.y);
        fclose(df);
    }
}

void joinFiles() {
    char ch;
    FILE *c, *i, *j;
    c = fopen ("chart.txt", "r");
    i = fopen ("intervals.txt", "r");
    j = fopen ("chart+intervals.txt", "w");
    while( ( ch = fgetc(c) ) != EOF )
      fputc(ch,j);

   while( ( ch = fgetc(i) ) != EOF )
      fputc(ch,j);
    fclose(c);
    fclose(i);
    fclose(j);
}

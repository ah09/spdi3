#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "basicStructures.h"
#include "draw.h"
#include "reach.h"
#include "sort.h"


/*extern */bool draw = false;

int main(int argc, char *argv[])
{
    //bool draw = false;
    if ( argc == 2 && !strcmp(argv[1], "-draw")) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf("drawing\n");
        draw = true;
    }
    int width;
    printf("enter number of regions wide\n");
    scanf("%d", &width);
    int height;
    printf("enter number of regions high\n");
    scanf("%d", &height);
    if (draw) {makeChart(width, height);}
    region * SPDI = malloc(sizeof(region) * width * height);
    int i = 0;
    for (i = 0; i < width * height; ++i) {
        printf("enter R%d.e.e1.pt1.x, R%d.e.e1.pt1.y, R%d.e.e1.pt2.x, R%d.e.e1.pt2.y, R%d.e.e2.pt1.x, R%d.e.e2.pt1.y, R%d.e.e2.pt2.x, R%d.e.e2.pt2.y, R%d.e.e3.pt1.x, R%d.e.e3.pt1.y, R%d.e.e3.pt2.x, R%d.e.e3.pt2.y, R%d.e.e4.pt1.x, R%d.e.e4.pt1.y, R%d.e.e4.pt2.x, R%d.e.e4.pt2.y\n", i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1, i+1);
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &SPDI[i].e.e1.pt1.x, &SPDI[i].e.e1.pt1.y, &SPDI[i].e.e1.pt2.x, &SPDI[i].e.e1.pt2.y, &SPDI[i].e.e2.pt1.x, &SPDI[i].e.e2.pt1.y, &SPDI[i].e.e2.pt2.x, &SPDI[i].e.e2.pt2.y, &SPDI[i].e.e3.pt1.x, &SPDI[i].e.e3.pt1.y, &SPDI[i].e.e3.pt2.x, &SPDI[i].e.e3.pt2.y, &SPDI[i].e.e4.pt1.x, &SPDI[i].e.e4.pt1.y, &SPDI[i].e.e4.pt2.x, &SPDI[i].e.e4.pt2.y);
        printf("enter R%d.v.a.x, R%d.v.a.y, R%d.v.b.x, R%d.v.b.y\n", i+1, i+1, i+1 ,i+1);
        scanf("%lf %lf %lf %lf", &SPDI[i].v.a.x, &SPDI[i].v.a.y, &SPDI[i].v.b.x, &SPDI[i].v.b.y);
    }
    if (draw) {
        for (i = 0; i < width * height; ++i) {
            addToChart(SPDI[i]);
        }
    }
    line start;
    printf("enter initial.pt1.x, initial.pt1.y, initial.pt2.x, initial.pt2.y\n");
    scanf("%lf %lf %lf %lf", &start.pt1.x, &start.pt1.y, &start.pt2.x, &start.pt2.y);
    line target;
    printf("enter target.pt1.x, target.pt1.y, target.pt2.x, target.pt2.y\n");
    scanf("%lf %lf %lf %lf", &target.pt1.x, &target.pt1.y, &target.pt2.x, &target.pt2.y);
    sort(&start.pt1.x, &start.pt1.y, &start.pt2.x, &start.pt2.y);
    sort(&target.pt1.x, &target.pt1.y, &target.pt2.x, &target.pt2.y);
    if (draw) {
        finishChart(start, target);
        addInterval(lineNotFound, start);
    }
    struct node* initial = NULL;
    initial = malloc(sizeof(struct node));
    initial->i = 0;
    initial->split = 0;
    initial->interval = start;
    initial->previous = NULL;
    line l = reach(SPDI, width * height, initial, target);
    if (l.pt1.x != -1) {
        printf("l is (%f, %f) to (%f, %f)\n", l.pt1.x, l.pt1.y, l.pt2.x, l.pt2.y);
    }
    else {printf("can't be reached\n");}
    if (draw) {joinFiles();}
    free(initial);

    return 0;
}

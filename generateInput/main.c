#include <stdio.h>
#include <stdlib.h>
#include "basicStructures.h"
#include "generateSPDI.h"
#include "sort.h"

int main()
{
    int width;
    printf("enter width\n");
    scanf("%d", &width);
    int height;
    printf("enter height\n");
    scanf("%d", &height);
    line I;
    printf("enter initial\n");
    scanf("%lf %lf %lf %lf", &I.pt1.x, &I.pt1.y, &I.pt2.x, &I.pt2.y);
    line e;
    printf("enter target edge\n");
    scanf("%lf %lf %lf %lf", &e.pt1.x, &e.pt1.y, &e.pt2.x, &e.pt2.y);

    sort(&I.pt1.x, &I.pt1.y, &I.pt2.x, &I.pt2.y);
    sort(&e.pt1.x, &e.pt1.y, &e.pt2.x, &e.pt2.y);

    region * SPDI = malloc(sizeof(region) * width * height);
    int customSize;
    printf("enter number of ready made regions\n");
    scanf("%d", &customSize);
    int i;
    for (i = 0; i < customSize; ++i) {
        int regionNumber;
        printf("enter region number (%d of %d)\n", i + 1, customSize);
        scanf("%d", &regionNumber);
        SPDI[regionNumber].e = *generateEdges(&SPDI[regionNumber], regionNumber % width, regionNumber / width);
        regionVectors v;
        printf("enter vectors\n");
        scanf("%lf %lf %lf %lf", &v.a.x, &v.a.y, &v.b.x, &v.b.y);
        SPDI[regionNumber].v = v;
    }
    SPDI = generateSPDI(SPDI, width, height);

    FILE * sf;

    sf = fopen ("sequential.in.txt", "w+");
    //fprintf(sf, "%d\n", width * height);
    fprintf(sf, "%d\n", width);
    fprintf(sf, "%d\n", height);
    for (i = 0; i < width * height; ++i) {
        fprintf(sf, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n%f %f %f %f\n", SPDI[i].e.e1.pt1.x, SPDI[i].e.e1.pt1.y, SPDI[i].e.e1.pt2.x, SPDI[i].e.e1.pt2.y, SPDI[i].e.e2.pt1.x, SPDI[i].e.e2.pt1.y, SPDI[i].e.e2.pt2.x, SPDI[i].e.e2.pt2.y, SPDI[i].e.e3.pt1.x, SPDI[i].e.e3.pt1.y, SPDI[i].e.e3.pt2.x, SPDI[i].e.e3.pt2.y, SPDI[i].e.e4.pt1.x, SPDI[i].e.e4.pt1.y, SPDI[i].e.e4.pt2.x, SPDI[i].e.e4.pt2.y, SPDI[i].v.a.x, SPDI[i].v.a.y, SPDI[i].v.b.x, SPDI[i].v.b.y);
    }
    fprintf(sf, "%f %f %f %f\n%f %f %f %f", I.pt1.x, I.pt1.y, I.pt2.x, I.pt2.y, e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);

    fclose(sf);


    FILE * pf;

    pf = fopen ("parallel.xml", "w+");
    fprintf(pf, "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>\n<record xmlns=\"snet-home.org\" type=\"data\" mode=\"textual\" interface=\"C4SNet\">\n  <tag label=\"size\">%d</tag>\n  <field label=\"SPDI\">(double[%d])%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", width * height, 20 * width * height, SPDI[0].e.e1.pt1.x, SPDI[0].e.e1.pt1.y, SPDI[0].e.e1.pt2.x, SPDI[0].e.e1.pt2.y, SPDI[0].e.e2.pt1.x, SPDI[0].e.e2.pt1.y, SPDI[0].e.e2.pt2.x, SPDI[0].e.e2.pt2.y, SPDI[0].e.e3.pt1.x, SPDI[0].e.e3.pt1.y, SPDI[0].e.e3.pt2.x, SPDI[0].e.e3.pt2.y, SPDI[0].e.e4.pt1.x, SPDI[0].e.e4.pt1.y, SPDI[0].e.e4.pt2.x, SPDI[0].e.e4.pt2.y, SPDI[0].v.a.x, SPDI[0].v.a.y, SPDI[0].v.b.x, SPDI[0].v.b.y);
    for (i = 1; i < width * height; ++i) {
        fprintf(pf, ",%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", SPDI[i].e.e1.pt1.x, SPDI[i].e.e1.pt1.y, SPDI[i].e.e1.pt2.x, SPDI[i].e.e1.pt2.y, SPDI[i].e.e2.pt1.x, SPDI[i].e.e2.pt1.y, SPDI[i].e.e2.pt2.x, SPDI[i].e.e2.pt2.y, SPDI[i].e.e3.pt1.x, SPDI[i].e.e3.pt1.y, SPDI[i].e.e3.pt2.x, SPDI[i].e.e3.pt2.y, SPDI[i].e.e4.pt1.x, SPDI[i].e.e4.pt1.y, SPDI[i].e.e4.pt2.x, SPDI[i].e.e4.pt2.y, SPDI[i].v.a.x, SPDI[i].v.a.y, SPDI[i].v.b.x, SPDI[i].v.b.y);
    }
    fprintf(pf, "</field>\n  <field label=\"I\">(double[4])%f,%f,%f,%f</field>\n  <field label=\"e\">(double[4])%f,%f,%f,%f</field>\n</record>\n<record xmlns=\"snet-home.org\" type=\"terminate\" />", I.pt1.x, I.pt1.y, I.pt2.x, I.pt2.y, e.pt1.x, e.pt1.y, e.pt2.x, e.pt2.y);

    fclose(pf);


    free(SPDI);

    return 0;
}

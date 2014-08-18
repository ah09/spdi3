#include "sort.h"


void swap(double *a, double *b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(double *x1, double *y1, double *x2, double *y2) {
    if (*x1 <= *x2 && *y1 <= *y2) return;
    if (*x1 > *x2) {
        swap(x1, x2);
        swap(y1, y2);
    }
    else if (*x1 == *x2) {
        swap(y1, y2);
    }
}

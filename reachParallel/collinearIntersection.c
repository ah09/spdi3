#include "basicStructures.h"
#include "collinearIntersection.h"
#include "findXorY.h"
#include "minmax.h"


line collinearIntersection(line I, line e) {
    line l;
    double AI = I.pt2.y - I.pt1.y;
    double Ae = e.pt2.y - e.pt1.y;
    double BI = I.pt1.x - I.pt2.x;
    double Be = e.pt1.x - e.pt2.x;
    double CI = AI*I.pt1.x + BI*I.pt1.y;
    double Ce = Ae*e.pt1.x + Be*e.pt1.y;
    if (AI*e.pt1.x + BI*e.pt1.y - CI == Ae*e.pt1.x + Be*e.pt1.y - Ce){
        if (I.pt1.x < I.pt2.x) {
            l.pt1.x = MAX(I.pt1.x, e.pt1.x);
            l.pt1.y = findY(l.pt1.x, I);
            l.pt2.x = MIN(I.pt2.x, e.pt2.x);
            l.pt2.y = findY(l.pt2.x, I);
            return l;
        }
        l.pt1.y = MAX(I.pt1.y, e.pt1.y);
        l.pt1.x = findX(l.pt1.y, I);
        l.pt2.y = MIN(I.pt2.y, e.pt2.y);
        l.pt2.x = findX(l.pt2.y, I);
        return l;
    }
    else {return lineNotFound;}
}

bool isCollinear(line I, line e) {
    double AI = I.pt2.y - I.pt1.y;
    double Ae = e.pt2.y - e.pt1.y;
    double BI = I.pt1.x - I.pt2.x;
    double Be = e.pt1.x - e.pt2.x;
    double CI = AI*I.pt1.x + BI*I.pt1.y;
    double Ce = Ae*e.pt1.x + Be*e.pt1.y;
    double d = AI*Be - Ae*BI;
    if (d == 0 && AI*e.pt1.x + BI*e.pt1.y - CI == Ae*e.pt1.x + Be*e.pt1.y - Ce) {return true;}
    return false;
}

bool isContainedIn(line I, line e) {
    if (isCollinear(I, e) && ((I.pt1.y == I.pt2.y && e.pt1.y == e.pt2.y && I.pt1.x >= e.pt1.x && I.pt2.x <= e.pt2.x)
        || (I.pt1.x == I.pt2.x && e.pt1.x == e.pt2.x && I.pt1.y >= e.pt1.y && I.pt2.y <= e.pt2.y))){
        return true;
    }
    return false;
}

bool isSomeCollinearIntersection(line I, line e) {
    double AI = I.pt2.y - I.pt1.y;
    double Ae = e.pt2.y - e.pt1.y;
    double BI = I.pt1.x - I.pt2.x;
    double Be = e.pt1.x - e.pt2.x;
    double CI = AI*I.pt1.x + BI*I.pt1.y;
    double Ce = Ae*e.pt1.x + Be*e.pt1.y;
    double d = AI*Be - Ae*BI;
    if (d == 0 && AI*e.pt1.x + BI*e.pt1.y - CI == Ae*e.pt1.x + Be*e.pt1.y - Ce
        && ((I.pt1.y == I.pt2.y && e.pt1.y == e.pt2.y && I.pt1.x != e.pt2.x && I.pt2.x != e.pt1.x && ((I.pt1.x >= e.pt1.x && I.pt1.x <= e.pt2.x) || (I.pt2.x <= e.pt2.x && I.pt2.x >=e.pt1.x)))
        || (I.pt1.x == I.pt2.x && e.pt1.x == e.pt2.x && I.pt1.y != e.pt2.y && I.pt2.y != e.pt1.y && ((I.pt1.y >= e.pt1.y && I.pt1.y <= e.pt2.y) || (I.pt2.y <= e.pt2.y && I.pt2.y >= e.pt1.y))))){
        return true;
    }
    return false;
}

line lineSetMinusLine(line I, line e) {
    line l;
    if (isSomeCollinearIntersection(I, e)) {
        if (I.pt1.x == I.pt2.x) {
            if (I.pt1.y < e.pt1.y) {
                l.pt1.x = I.pt1.x;
                l.pt1.y = I.pt1.y;
                l.pt2.x = I.pt2.x;
                l.pt2.y = e.pt1.y;
                return l;
            }
            else if (I.pt2.y > e.pt2.y) {
                l.pt1.x = I.pt1.x;
                l.pt1.y = e.pt2.y;
                l.pt2.x = I.pt2.x;
                l.pt2.y = I.pt2.y;
                return l;
            }
        }
        else {
            if (I.pt1.x < e.pt1.x) {
                l.pt1.x = I.pt1.x;
                l.pt1.y = I.pt1.y;
                l.pt2.x = e.pt1.x;
                l.pt2.y = e.pt1.y;
                return l;
            }
            else if (I.pt2.x > e.pt2.x) {
                l.pt1.x = e.pt2.x;
                l.pt1.y = e.pt2.y;
                l.pt2.x = I.pt2.x;
                l.pt2.y = I.pt2.y;
                return l;
            }
        }
        return lineNotFound;
    }
    return I;
}

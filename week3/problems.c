#include <math.h>
#include <stdlib.h>

#include "p1.c"

int p2() {
    float Ax = -4.0f, Ay = -1.0f;
    float Bx = -5.0f, By = 5.0f;
    float Cx = 2.0f, Cy = 0.0f;
    float Dx = -3.0f, Dy = -5.0f;
    float Ex = -3.0f, Ey = -4.0f;

    float pointX, pointY;
    scanf("%f %f", &pointX, &pointY);

    const float bigRadiusSq = (Ax - Bx) * (Ax - Bx) + (Ay - By) * (Ay - By);
    const float smallRadiusSq = (Dx - Ex) * (Dx - Ex) + (Dy - Ey) * (Dy - Ey);

    const int inBigCircle = (Ax - pointX) * (Ax - pointX) + (Ay - pointY) * (Ay - pointY) < bigRadiusSq;
    const int outSmallCircle =
            (Dx - pointX) * (Dx - pointX) + (Dy - pointY) * (Dy - pointY) > smallRadiusSq;
    const int outOfSegment = (pointX <= -5 || pointY <= -1) ||
                             // If the point is not in the section where the segment is, do not do the aritmetics
                             (((Bx - Ax) * (pointY - Ay) - (By - Ay) * (pointX - Ax)) > 0 &&
                              ((Cx - Ax) * (pointY - Ay) - (Cy - Ay) * (pointX - Ax)) < 0);

    printf("%d\n", inBigCircle && outSmallCircle && outOfSegment);

    return inBigCircle && outSmallCircle && outOfSegment;
}

int p3() {
    float Ax = -2.0f, Ay = -1.0f;
    float Bx = 1.0f, By = 5.0f;
    float Cx = -5.0f, Cy = 3.0f;
    float Dx = -1.0f, Dy = 4.0f;
    float Ex = -1.0f, Ey = 5.0f;

    float pointX, pointY;
    scanf("%f %f", &pointX, &pointY);

    const float bigRadiusSq = (Ax - Bx) * (Ax - Bx) + (Ay - By) * (Ay - By);
    const float smallRadiusSq = (Dx - Ex) * (Dx - Ex) + (Dy - Ey) * (Dy - Ey);

    const int inBigCircle = (Ax - pointX) * (Ax - pointX) + (Ay - pointY) * (Ay - pointY) < bigRadiusSq;
    const int outSmallCircle = (Dx - pointX) * (Dx - pointX) + (Dy - pointY) * (Dy - pointY) > smallRadiusSq;
    const int inSegment = ((Bx - Ax) * (pointY - Ay) - (By - Ay) * (pointX - Ax)) < 0 &&
                          ((Cx - Ax) * (pointY - Ay) - (Cy - Ay) * (pointX - Ax)) > 0;

    return inBigCircle && outSmallCircle && inSegment;
}

int p4() {
    int startX = 1, startY = 1;
    int endX = 2, endY = 2;

    scanf("%d %d %d %d", &startX, &startY, &endX, &endY);

    const int canHorse = (abs(endX - startX) == 2 && abs(endX - startX) == 1) ||
                         (abs(endX - startX) == 1 && abs(endX - startX) == 2);

    const int canKing = (startX - endX) * (startX - endX) && (startY - endY) * (startY - endY);

    const int canBishop = (startX == endX && startY != endY) && (startX != endX && startY == endY);

    const int canTower = abs(endX - startX) == abs(endY - startY);

    const int canQueen = canKing && canBishop && canTower;

    printf("Horse: %d\n", canHorse);
    printf("King: %d\n", canKing);
    printf("Tower: %d\n", canTower);
    printf("Bishop: %d\n", canBishop);
    printf("Queen: %d\n", canQueen);

    return 0;
}


int p5() {
    int A, B, C, D;
    scanf("%d %d", &A, &B);
    scanf("%d %d", &C, &D);

    int min = (B + D - abs(B - D)) / 2;
    int max = (A + C + abs(A - C)) / 2;

    int sum = min + max;

    printf("Sum: %d\n", sum);

    return sum;
}

int p6() {
    float x1, y1, w1, h1;
    float x2, y2, w2, h2;

    scanf("%f %f %f %f", &x1, &y1, &w1, &h1);
    scanf("%f %f %f %f", &x2, &y2, &w2, &h2);

    int cross = (x1 + w1) <= x2 || x2 + w2 <= x1 || y1 + h1 <= y2 || y2 + h2 <= y1;

    printf("%d\n", cross);

    return 0;
}

float p7() {
    float x1, y1, w1, h1;
    float x2, y2, w2, h2;

    scanf("%f %f %f %f", &x1, &y1, &w1, &h1);
    scanf("%f %f %f %f", &x2, &y2, &w2, &h2);

    float overlap_w = fmax(0, fmin(x1 + w1, x2 + w2) - fmax(x1, x2));
    float overlap_h = fmax(0, fmin(y1 + h1, y2 + h2) - fmax(y1, y2));

    float area = overlap_w * overlap_h;

    printf("%.2f\n", area);

    return area;
}

int p8() {
    float r, px, py;
    scanf("%f %f %f", &r, &px, &py);

    float d2 = px * px + py * py;
    float r2 = r * r;

    int inside = d2 < r2;
    int on = fabs(d2 - r2) < 1e-6;
    int outside = d2 > r2;

    printf("Inside %d\n", inside);
    printf("On %d\n", on);
    printf("Outside %d\n", outside);

    return 0;
}

int p9() {
    double r, cx, cy;
    double x1, y1, x2, y2;

    printf("Insert Circle params (radius, x, y): ");
    scanf("%lf %lf %lf", &r, &cx, &cy);

    printf("Insert rectangle params (point 1, point2): ");
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);

    double dx = cx - fmax(x1, fmin(cx, x2));
    double dy = cy - fmax(y1, fmin(cy, y2));

    const char *ans[] = {"false", "true"};

    printf("Output: %s\n", ans[(dx * dx + dy * dy) <= (r * r)]);
    return 0;
}

int p10() {
    int h, m, s;
    scanf("%d:%d:%d", &h, &m, &s);

    s = s + 1;
    m = m + s / 60;
    s = s % 60;
    h = (h + m / 60) % 24;
    m = m % 60;

    printf("%02d:%02d:%02d\n", h, m, s);

    return 0;
}

int main() {
    p2();
    return 0;
}

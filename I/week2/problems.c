#include <stdio.h>
#include <math.h>

void p2() {
    short s = -8;
    int i = 67;
    float f = 69.420f;
    char c = 'O';
    printf("%hd %d %.1f %c\n", s, i, f, c);
    s = -32;
    i = 76;
    f = 420.69f;
    c = 'v';
    printf("%hd %d %.1f %c\n", s, i, f, c);
}

void p3() {
    short s;
    int i;
    float f;
    char c;
    scanf("%hd%d%f %c", &s, &i, &f, &c);
    printf("%hd\n"
           "%d\n"
           "%.1f\n"
           "%c\n", s, i, f, c);
}

void p4() {
    const double PI = 3.141592653589793;
    double deg;
    scanf("%lf", &deg);
    printf("%.6f\n", PI / 180.0 * deg);
}

void p5() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("Sum:%d\n"
           "Diff:%d\n"
           "Prod:%d\n"
           "Div:%d\n"
           "Rem:%d\n", a + b, a - b, a * b, a / b, a % b);
    float x, y;
    scanf("%f%f", &x, &y);
    printf("Sum:%.2f\n"
           "Diff:%.2f\n"
           "Prod:%.2f\n"
           "Div:%.2f\n", x + y, x - y, x * y, x / y);
}

void p6() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    int p = a * b * c, r = p % 6;
    printf("Product:%d\n"
           "Remainder:%d\n", p, r);
}

void p7() {
    int n;
    scanf("%d", &n);
    int d1 = n / 10000, d2 = (n / 1000) % 10, d3 = (n / 100) % 10, d4 = (n / 10) % 10, d5 = n % 10;
    printf("Normal:%d %d %d %d %d\n"
           "Reversed:%d %d %d %d %d\n"
           "Sum:%d\n", d1, d2, d3, d4, d5, d5, d4, d3, d2, d1,
           d1 + d2 + d3 + d4 + d5);
}

void p8() {
    int x, y, t;
    scanf("%d%d", &x, &y);
    t = x;
    x = y;
    y = t;
    printf("%d %d\n", x, y);
    x = x + y;
    y = x - y;
    x = x - y;
    printf("%d %d\n", x, y);
}

void p9() {
    int x, y, z, t;
    scanf("%d%d%d", &x, &y, &z);
    t = x;
    x = y;
    y = z;
    z = t;
    printf("Temp:x=%d y=%d z=%d\n", x, y, z);
    t = z;
    z = y;
    y = x;
    x = t;
    x = x + y + z;
    y = x - (y + z);
    z = x - (y + z);
    x = x - (y + z);
    printf("Arith:x=%d y=%d z=%d\n", x, y, z);
}

void p10() {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", (int) (pow(a + b, 4) - pow(a - b, 2)));
}

void p11() {
    double b;
    scanf("%lf", &b);
    printf("%.2lf\n", b / 1.9558);
}

void p12() {
    int y;
    scanf("%d", &y);
    printf("%d %d\n", y, (y % 4 == 0) && (y % 100 != 0 || y % 400 == 0));
}

void p13() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("%d\n", (a + b > c) && (a + c > b) && (b + c > a));
}

void p14() {
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);
    double v = (a + b > c) && (a + c > b) && (b + c > a), p = (a + b + c) / 2.0;
    printf("Per:%.2f\nArea:%.2f\n", v ? (a + b + c) : -1, v ? sqrt(p * (p - a) * (p - b) * (p - c)) : -1);
}

void p15() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    printf("Pos:%d\nNeg:%d\n", (a > 0) + (b > 0) + (c > 0), (a < 0) + (b < 0) + (c < 0));
}

int main() {
    p2();
    return 0;
}

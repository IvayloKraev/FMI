#include <math.h>
#include <stdint.h>
#include <stdio.h>

int p1() {
    uint8_t age;

    scanf("%hhd", &age);

    if (age >= 18) {
        printf("You are a minor.\n");
    } else {
        printf("You are an adult.\n");
    }

    return age >= 18;
}

int p2() {
    uint8_t m, y;
    scanf("%hhd %hhd", &m, &y);
    uint8_t d;
    switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            d = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            d = 30;
            break;
        case 2:
            if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
                d = 29;
            else
                d = 28;
            break;
        default: d = 0;
    }
    printf("%hhd\n", d);
    return d;
}

int p3() {
    uint32_t a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    uint32_t t;
    // Custom bubble sort for only three nums
    if (a > b) {
        t = a;
        a = b;
        b = t;
    }
    if (b > c) {
        t = b;
        b = c;
        c = t;
    }
    if (a > b) {
        t = a;
        a = b;
        b = t;
    }

    printf("%d %d %d\n", a, b, c);
    return 0;
}

int p4() {
    uint32_t n;
    scanf("%d", &n);

    uint8_t found = 0;
    for (uint8_t i = 0; i * i <= n; i++) {
        if (i * i == n) {
            printf("Числото е квадрат на %d.\n", i);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Числото не е квадрат на цяло число.\n");

    return found;
}

int p5() {
    uint32_t x1, x2, y1, y2;
    scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2);

    if ((x1 * x2 - y1 * y2) == 0) {
        printf("Perpendicular");
    } else {
        printf("Not Perpendicular");
    }
}

int p6() {
    uint8_t n;
    scanf("%hhd", &n);


    int tens = n / 10;
    int ones = n % 10;

    switch (tens) {
        case 1: printf("X");
            break;
        case 2: printf("XX");
            break;
        case 3: printf("XXX");
            break;
        case 4: printf("XL");
            break;
        case 5: printf("L");
            break;
        case 6: printf("LX");
            break;
        case 7: printf("LXX");
            break;
        case 8: printf("LXXX");
            break;
    }

    switch (ones) {
        case 1: printf("I");
            break;
        case 2: printf("II");
            break;
        case 3: printf("III");
            break;
        case 4: printf("IV");
            break;
        case 5: printf("V");
            break;
        case 6: printf("VI");
            break;
        case 7: printf("VII");
            break;
        case 8: printf("VIII");
            break;
        case 9: printf("IX");
            break;
    }

    printf("\n");
    return 0;
}

int p7() {
    uint32_t a, b, c;

    scanf("%d %d %d", &a, &b, &c);

    double D, x1, x2;

    if (a == 0) {
        x1 =
                printf("This is not a quadratic equation.\n");
        return 0;
    }

    D = b * b - 4 * a * c;

    if (D > 0) {
        x1 = (-b + sqrt(D)) / (2 * a);
        x2 = (-b - sqrt(D)) / (2 * a);
        printf("Two real roots: x1 = %.2lf, x2 = %.2lf\n", x1, x2);
    } else if (D == 0) {
        x1 = -b / (2 * a);
        printf("One real root: x = %.2lf\n", x1);
    } else {
        printf("No real roots.\n");
    }

    return 0;
}

int p8() {
    uint32_t a;
    scanf("%d", &a);

    uint32_t mshbMask = 0b1111 << 28, lshbMask = 0b1111;
    uint8_t mshb = (a & mshbMask) >> 28, lshb = a & lshbMask;

    mshb == lshb ? printf("Yes\n") : printf("No\n");

    return mshb == lshb;
}

int p9() {
    uint16_t n;
    scanf("%hd", &n);

    uint8_t a = n / 1000,
            b = n / 100 % 10,
            c = n / 10 % 10,
            d = n % 10;

    uint8_t max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    if (d > max) {
        max = d;
    }

    uint8_t min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    if (d < min) {
        min = d;
    }

    printf("%d\n", max - min);
    return max - min;
}

int p10() {
    uint64_t x1, y1, r1;
    scanf("%llu %llu %llu", &x1, &y1, &r1);
    uint64_t x2, y2, r2;
    scanf("%llu %llu %llu", &x2, &y2, &r2);

    uint64_t distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    if (distance == 0) {
        r1 == r2 ? printf("Identical circles\n") : printf("Concentric\n");
    } else if (distance > (r1 + r2) * (r1 + r2)) {
        printf("Disjoint\n");
    } else if (distance == (r1 + r2) * (r1 + r2)) {
        printf("External tangent\n");
    } else if (distance == (r1 > r2 ? r1 - r2 : r2 - r1) * (r1 > r2 ? r1 - r2 : r2 - r1)) {
        printf("Internal tangent\n");
    } else if (distance > (r1 > r2 ? r1 - r2 : r2 - r1) * (r1 > r2 ? r1 - r2 : r2 - r1)) {
        printf("One circle is strictly inside the other\n");
    } else {
        printf("Intersect at two points\n");
    }

    return 0;
}

int p11() {
    uint32_t a1, a2, b1, b2, c1, c2;
    scanf("%d %d", &a1, &a2);
    scanf("%d %d", &b1, &b2);
    scanf("%d %d", &c1, &c2);

    uint32_t m1, m2;
    scanf("%d %d", &m1, &m2);

    int64_t cAB = (b1 - a1) * (m2 - a2) - (b2 - a2) * (m1 - a1);
    int64_t cBC = (c1 - b1) * (m2 - b2) - (c2 - b2) * (m1 - b1);
    int64_t cCA = (a1 - c1) * (m2 - c2) - (a2 - c2) * (m1 - c1);

    if ((cAB >= 0 && cBC >= 0 && cCA >= 0) || (cAB <= 0 && cBC <= 0 && cCA <= 0)) {
        printf("Inside\n");
    } else {
        printf("Outside\n");
    }
}

int main(void) {
    p9();
    return 0;
}

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int p1() {
    unsigned int a, b;

    printf("Въведете две цели неотрицателни числа: ");
    scanf("%u %u", &a, &b);

    const unsigned int notA = ~a;
    const unsigned int notB = ~b;
    const unsigned int andAB = a & b;
    const unsigned int orAB = a | b;
    const unsigned int xorAB = a ^ b;

    printf("a & b : %u\n", andAB);
    printf("a | b : %u\n", orAB);
    printf("a ^ b : %u\n", xorAB);
    printf("~a : %u\n", notA);
    printf("~b : %u\n", notB);

    return 0;
}

int p2() {
    unsigned int num, n;

    scanf("%u %u", &num, &n);

    const unsigned int leftShift = num << n;
    const unsigned int rightShift = num >> n;

    printf("num << n = %u\n", leftShift);
    printf("num >> n = %u\n", rightShift);

    return 0;
}

int p3() {
    unsigned int num;

    scanf("%u", &num);

    const int result = 1 << num;

    printf("%u\n", result);

    return 0;
}

int p4() {
    int32_t num, n;

    scanf("%u %u", &num, &n);

    int msb = (num >> 31) & 1,
            lsb = num & 1,
            nb = (num >> n) & 1;

    printf("%u\n", msb);
    printf("%u\n", lsb);
    printf("%u\n", nb);

    return 0;
}

int p5() {
    int32_t num;

    scanf("%d", &num);

    int8_t powerOf2 = !!num && (num & num - 1) == 0;

    printf("%d\n", powerOf2);

    return powerOf2;
}

int p6() {
    int8_t n, r = 0;
    scanf("%hhu", &n);
    r |= (n & 0x80) >> 7 | (n & 0x40) >> 5 | (n & 0x20) >> 3 | (n & 0x10) >> 1 |
            (n & 0x08) << 1 | (n & 0x04) << 3 | (n & 0x02) << 5 | (n & 0x01) << 7;
    printf("%d", n == r);

    return n == r;
}

uint32_t p7() {
    uint32_t N;
    uint8_t i, j, k;

    scanf("%hd", &N);
    scanf("%d %d %d", &i, &j, &k);

    N &= ~(1u << i);
    N |= (1u << j);
    N ^= (1u << k);

    printf("%d", N);

    return N;
}

int p8() {
    uint32_t N, i, j;
    scanf("%u %u %u", &N, &i, &j);

    uint32_t bit_i = (N >> i) & 1;
    uint32_t bit_j = (N >> j) & 1;

    N ^= (bit_i ^ bit_j) << i;
    N ^= (bit_i ^ bit_j) << j;

    printf("%u", N);
    return N;
}

uint32_t p9() {
    uint16_t year;
    uint8_t month, day;

    scanf("%hd %hhd %hhd", &year, &month, &day);

    uint32_t data = 0;

    data |= (year << 16) | (month << 8) | day;

    const uint16_t yearOut = (data >> 16);
    const uint8_t monthOut = (data >> 8), dayOut = data;

    printf("%hd %hhd %hhd", yearOut, monthOut, dayOut);

    return data;
}

int p10() {
    srand(time(NULL));

    uint8_t parent1, parent2;

    scanf("%hhd %hhd", &parent1, &parent2);

    uint8_t crossGene = rand() % 7 + 1;

    uint8_t crossMask = (1u << crossGene) - 1;


    uint8_t child1 = (parent1 & ~crossMask) | (parent2 & crossMask),
            child2 = (parent2 & ~crossMask) | (parent1 & crossMask);

    printf("%x\n%x", child1, child2);

    return 0;
}

int p11() {
    uint16_t time1, time2;

    scanf("%hd %hd", &time1, &time2);

    const uint16_t maskFormat = 0b0001000000000000,
            maskHoursFirstNum = 0b0000110000000000,
            maskHoursSecondNum = 0b0000001111000000,
            maskMins = 0b0000000000111111;

    const uint16_t invalidHour1 = ((time1 & maskHoursSecondNum) >> 6) > 9,
            invalidMins1 = (time1 & maskMins) > 59,
            invalidHour2 = ((time2 & maskHoursSecondNum) >> 6) > 9,
            invalidMins2 = (time2 & maskMins) > 59;

    printf("Invalid time: %d\n", invalidHour1 || invalidMins1 || invalidHour2 || invalidMins2);

    const uint16_t format1 = (time1 & maskFormat) >> 12,
            hours1 = ((time1 & maskHoursFirstNum) >> 10) * 10 + ((time1 & maskHoursSecondNum) >> 6),
            formatedHour1 = hours1 - (hours1 > 12 && (~format1 & 1)) * 12,
            minutes1 = time1 & maskMins;

    const uint16_t format2 = time2 & maskFormat,
            hours2 = ((time2 & maskHoursFirstNum) >> 10) * 10 + ((time2 & maskHoursSecondNum) >> 6),
            formatedHour2 = hours2 - (hours2 > 12 && (~format2 & 1)) * 12,
            minutes2 = time2 & maskMins;

    printf("%02hd:%02hd\n", formatedHour1, minutes1);
    printf("%02hd:%02hd\n", formatedHour2, minutes2);

    const uint16_t diffMinsTotal = (hours1 * 60 + minutes1) - (hours2 * 60 + minutes2),
            diffHours = diffMinsTotal / 60,
            diffMins = diffMinsTotal % 60;

    printf("diff: %02d:%02d\n", diffHours, diffMins);

    return 0;
}

int main() {
    p11();
    return 0;
}

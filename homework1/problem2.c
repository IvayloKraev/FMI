#include "stdio.h"
#include "stdint.h"

int main() {
    uint32_t a, b, k;
    if (scanf("%u %u %u", &a, &b, &k) != 3) {
        printf("Invalid input\n");
        return 0;
    }

    if (a > b || k == 0) {
        printf("Invalid input\n");
        return 0;
    }

    for (uint32_t i = a; i <= b; i++) {
        uint32_t copy = i;

        uint32_t tmp = copy;
        uint32_t digits = 0;
        if (tmp == 0) {
            digits = 1;
        } else {
            while (tmp > 0) {
                digits++;
                tmp /= 10;
            }
        }

        if (k > digits) {
            continue;
        }

        uint32_t powNum = 1;
        for (uint32_t j = 1; j < k; j++) {
            powNum *= 10;
        }

        uint32_t low = copy % powNum;
        uint32_t high_and_digit = copy / powNum;
        uint32_t high = high_and_digit / 10;

        copy = high * powNum + low;

        uint32_t reverse = 0, copyTmp = copy;

        while (copyTmp > 0) {
            reverse = reverse * 10 +  copyTmp % 10;
            copyTmp /= 10;
        }

        if (copy == reverse) {
            printf("%u\n", i);
        }

    }

    return 0;
}

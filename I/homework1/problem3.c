#include <stdint.h>

#include "stdio.h"

#define DAY 1
#define MONTH 11
#define YEAR 2025

int main() {
    uint32_t barcode;
    scanf("%d", &barcode);

    uint32_t dayMask = 0b00000000000000000000000000011111,
            monthMask = 0b00000000000000000000000111100000,
            yearMask = 0b0000000000000011111111000000000,
            expirationDaysMask = 0b01111111111111000000000000000000,
            checkMask = 0b10000000000000000000000000000000;

    uint32_t creationDay = barcode & dayMask,
            creationMonth = (barcode & monthMask) >> 5,
            creationYear = ((barcode & yearMask) >> 9) + 1900,
            expirationDays = (barcode & expirationDaysMask) >> 18;


    uint8_t sumOfOnes = 0;
    for (uint8_t i = 0; i < 31; i++) {
        sumOfOnes += barcode >> i & 1U;
    }


    if (sumOfOnes % 2 != (barcode & checkMask) >> 31) {
        printf("Invalid");
        return 0;
    }

    while (expirationDays > 0) {
        int leap = (creationYear % 400 == 0) || (creationYear % 4 == 0 && creationYear % 100 != 0);

        int dim;
        if (creationMonth == 1 || creationMonth == 3 || creationMonth == 5 || creationMonth == 7 ||
            creationMonth == 8 || creationMonth == 10 || creationMonth == 12) {
            dim = 31;
            } else if (creationMonth == 4 || creationMonth == 6 || creationMonth == 9 || creationMonth == 11) {
                dim = 30;
            } else {
                dim = leap ? 29 : 28;
            }

        if (creationDay + expirationDays <= dim) {
            creationDay += expirationDays;
            expirationDays = 0;
        } else {
            expirationDays -= (dim - creationDay + 1);
            creationDay = 1;
            creationMonth++;

            if (creationMonth > 12) {
                creationMonth = 1;
                creationYear++;
            }
        }
    }

    if (creationYear > YEAR || ( creationYear == YEAR && creationMonth > MONTH) || ( creationYear == YEAR && creationMonth == MONTH && creationDay >= DAY)) {
        printf("Good");
    } else {
        printf("Too old");
    }

    return 0;
}

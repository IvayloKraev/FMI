#include <assert.h>
#include <stdio.h>
#include <stdint.h>

static uint8_t image[25][25] = {0};
static char commands[41] = {0};

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void getImage(uint8_t currImage[25][25], uint8_t *N) {
    char str[26];

    scanf("%25s", str);

    int width = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        currImage[0][i] = str[i] - '0';
        width++;
    }

    for (int y = 1; y < width; y++) {
        scanf("%25s", str);
        for (size_t x = 0; x < width; x++) {
            currImage[y][x] = str[x] - '0';
        }
    }

    *N = width;
}

void getCommands(char *currCommands, uint8_t *numCommands) {
    assert(currCommands);
    assert(numCommands && *numCommands == 0);
    char str[41];
    scanf("%40s", str);

    for (size_t i = 0; str[i] != '\0'; i++) {
        currCommands[i] = str[i];
        (*numCommands)++;
    }
}

uint8_t removeMs(char *currCommands, const uint8_t *numCommands) {
    uint8_t newSize = 0;
    for (size_t i = 0; i < *numCommands; i++) {
        if (currCommands[i] != 'M') {
            currCommands[newSize] = currCommands[i];
            newSize++;
        }
    }

    return newSize;
}

// Make empty commands to 'M'
void filterCommands(char *currCommands, uint8_t *numCommands) {
    assert(currCommands);
    assert(numCommands);

    // U <index>
    for (size_t i = 0; i < *numCommands; i++) {
        if (currCommands[i] == 'U') {
            uint8_t indexToRemove = currCommands[i + 1] - '0';
            currCommands[indexToRemove] = 'M';
            currCommands[i] = 'M';
            currCommands[i + 1] = 'M';
        }
    }
    *numCommands = removeMs(currCommands, numCommands);

    // Combine LLL to R or RRR to L
    for (size_t i = 0; i < *numCommands - 2; i++) {
        if (currCommands[i] == 'L' && currCommands[i + 1] == 'L' && currCommands[i + 2] == 'L') {
            currCommands[i] = 'R';
            currCommands[i + 1] = 'M';
            currCommands[i + 2] = 'M';
        } else if (currCommands[i] == 'R' && currCommands[i + 1] == 'R' && currCommands[i + 2] == 'R') {
            currCommands[i] = 'L';
            currCommands[i + 1] = 'M';
            currCommands[i + 2] = 'M';
        }
    }
    *numCommands = removeMs(currCommands, numCommands);


    // Combine LR, HH, VV to M
    for (size_t i = 0; i < *numCommands - 1; i++) {
        if ((currCommands[i] == 'L' && currCommands[i + 1] == 'R') ||
            (currCommands[i] == 'R' && currCommands[i + 1] == 'L')) {
            currCommands[i] = 'M';
            currCommands[i + 1] = 'M';
        } else if (currCommands[i] == 'H' && currCommands[i + 1] == 'H') {
            currCommands[i] = 'M';
            currCommands[i + 1] = 'M';
        } else if (currCommands[i] == 'V' && currCommands[i + 1] == 'V') {
            currCommands[i] = 'M';
            currCommands[i + 1] = 'M';
        }
    }
    *numCommands = removeMs(currCommands, numCommands);
}

void R(uint8_t currImage[25][25], uint8_t n) {
    for (int layer = 0; layer < n / 2; layer++) {
        const int first = layer,
                last = n - 1 - layer;

        for (int i = first; i < last; i++) {
            const int offset = i - first,
                    top = currImage[first][i];

            currImage[first][i] = currImage[last - offset][first];
            currImage[last - offset][first] = currImage[last][last - offset];
            currImage[last][last - offset] = currImage[i][last];
            currImage[i][last] = top;
        }
    }
}

void L(uint8_t currImage[25][25], uint8_t n) {
    for (int layer = 0; layer < n / 2; layer++) {
        int first = layer,
            last  = n - 1 - layer;

        for (int i = first; i < last; i++) {
            int offset = i - first,
                top = currImage[first][i];

            currImage[first][i] = currImage[i][last];
            currImage[i][last] = currImage[last][last - offset];
            currImage[last][last - offset] = currImage[last - offset][first];
            currImage[last - offset][first] = top;
        }
    }
}

void H(uint8_t currImage[25][25], uint8_t n) {
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            int tmp = currImage[i][j];
            currImage[i][j] = currImage[n - 1 - i][j];
            currImage[n - 1 - i][j] = tmp;
        }
    }
}

void V(uint8_t currImage[25][25], uint8_t n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n / 2; j++) {
            int tmp = currImage[i][j];
            currImage[i][j] = currImage[i][n - 1 - j];
            currImage[i][n - 1 - j] = tmp;
        }
    }
}

void S(uint8_t currImage[25][25], uint8_t n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j) putchar(' ');
            printf("%d", currImage[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    uint8_t n = 0, numCommands = 0;
    getImage(image, &n);
    getCommands(commands, &numCommands);
    filterCommands(commands, &numCommands);

    for (int i = 0; i < numCommands; i++) {
        if (commands[i] == 'R') {
            R(image, n);
        } else if (commands[i] == 'L') {
            L(image, n);
        } else if (commands[i] == 'H') {
            H(image, n);
        } else if (commands[i] == 'V') {
            V(image, n);
        } else if (commands[i] == 'S' || commands[i] == 'E') {
            S(image, n);
        }
    }
}

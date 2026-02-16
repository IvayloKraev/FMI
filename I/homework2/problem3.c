#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define COLS 7
#define ROWS 6

#define DEFAULT 'X'
#define PLAYER 'r'
#define COMPUTER 'y'

#define ERR_OK              (-100)
#define ERR_INVALID_COL     (-101)
#define ERR_INVALID_ROW     (-102)

#define GAME_WON_NOT (-50)
#define GAME_WON     (-51)

char field[ROWS][COLS] = {
    {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT},
    {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT},
    {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT},
    {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT},
    {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT},
    {DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT, DEFAULT},
};

void printField(char currentField[ROWS][COLS]) {
    assert(currentField);

    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++) {
            printf(" %c ", currentField[i][j]);
        }
        printf("\n");
    }
}

int8_t playTurn(char currentField[ROWS][COLS], uint8_t col, char turn) {
    assert(currentField);
    assert(turn == PLAYER || turn == COMPUTER);

    if (col == 0 || col > COLS) {
        return ERR_INVALID_COL;
    }
    --col;

    if (currentField[0][col] != DEFAULT) {
        return ERR_INVALID_ROW;
    }

    for (size_t i = ROWS; i > 0; i--) {
        if (currentField[i - 1][col] == DEFAULT) {
            currentField[i - 1][col] = turn;
            break;
        }
    }
    return ERR_OK;
}


int8_t checkField(char currentField[ROWS][COLS], char turn) {
    assert(currentField);
    assert(turn == 'r' || turn == 'y');

    const uint8_t dirs[4][2] = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    for (size_t row = 0; row < ROWS; row++) {
        for (size_t col = 0; col < COLS; col++) {
            if (currentField[row][col] != turn) continue;
            for (int d = 0; d < 4; d++) {
                uint8_t currR = row, currC = col;
                uint8_t k = 0;

                for (k = 1; k < 4; k++) {
                    currR += dirs[d][0];
                    currC += dirs[d][1];
                    if (currR < 0 || currR >= ROWS || currC < 0 || currC >= COLS) break;
                    if (currentField[currR][currC] != turn) break;
                }

                if (k == 4) return GAME_WON;
            }
        }
    }

    return GAME_WON_NOT;
}


int main() {
    srand(time(NULL));
    do {
        printField(field);
        do {
            uint8_t colPlayer;
            scanf("%hhd", &colPlayer);
            int8_t error = playTurn(field, colPlayer, PLAYER);
            if (error == ERR_OK) {
                break;
            }
            printf("Player error: %d\n", error);
        } while (1);

        if (checkField(field, PLAYER) == GAME_WON) {
            printf("Player Won!!");
            break;
        }

        do {
            uint8_t colComp = rand() % COLS + 1;
            int8_t error = playTurn(field, colComp, COMPUTER);
            if (error == ERR_OK) {
                break;
            }
        } while (1);
        if (checkField(field, PLAYER) == GAME_WON) {
            printf("Computer Won!!");
            break;
        }
    } while (1);

    return 0;
}

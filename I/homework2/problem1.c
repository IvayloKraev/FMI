#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define PLAY_NUM_SIZE 4

#define MAX_CANDIDATES 4536

static uint8_t candidates[MAX_CANDIDATES][PLAY_NUM_SIZE] = {0};
static uint16_t candidateCount = 0;

// Because we haven't learned enums
#define ERR_OK                  (-100)
#define ERR_NEGATIVE_NUM        (-101)
#define ERR_LEAD_ZERO           (-102)
#define ERR_NUM_OFB             (-103) // Number out of boundaries
#define ERR_REPEATING_DIGITS    (-104)

#define GAME_WON_NOT            (-50)
#define GAME_WON_COMP           (-51)
#define GAME_WON_PLAYER         (-52)
#define GAME_CHEAT_PLAYER       (-53)


void userErrorMessage(int8_t errorCode) {
    switch (errorCode) {
        case ERR_NEGATIVE_NUM:
            printf("You've entered a negative number");
            break;
        case ERR_LEAD_ZERO:
            printf("You've entered a number with leading zero");
            break;
        case ERR_NUM_OFB:
            printf("You've entered number not in [1000, 9999]");
            break;
        case ERR_REPEATING_DIGITS:
            printf("You've entered number with repeating digits");
            break;
        default: printf("Something's wrong, I can feel it");
    }
    printf("\n\n");
}

void generateNumber(uint8_t num[4]) {
    assert(num); // WHAT SHOULD I USE FOR nullptr
    // Should I chek for size

    uint8_t usedNums[10] = {0};

    for (int i = 0; i < PLAY_NUM_SIZE;) {
        const uint8_t genDigit = rand() % 10;

        if (i == 0 && genDigit == 0) continue;
        if (usedNums[genDigit]) continue;

        num[i++] = genDigit;
        usedNums[genDigit] = 1;
    }
}

void computeBullsAndCows(const uint8_t inputNum[], const uint8_t compNum[], uint8_t *const numBulls,
                         uint8_t *const numCows) {
    assert(inputNum);
    assert(compNum);
    assert(numBulls && *numBulls == 0);
    assert(numCows && *numCows == 0);

    uint8_t usedNums[10] = {0};

    for (int i = 0; i < PLAY_NUM_SIZE; i++) {
        usedNums[compNum[i]] = 1;
    }

    for (int i = 0; i < PLAY_NUM_SIZE; i++) {
        const uint8_t bull = inputNum[i] == compNum[i];
        *numBulls += bull;
        *numCows += !bull * usedNums[inputNum[i]];
    }
}

int8_t parseInputNum(const int32_t input, uint8_t num[]) {
    assert(num);
    if (input < 0) return ERR_NEGATIVE_NUM;
    if (input / 1000 == 0) return ERR_LEAD_ZERO;
    if (input < 1000 || input > 9999) return ERR_NUM_OFB;

    uint8_t usedNums[10] = {0};
    usedNums[input / 1000]++;
    usedNums[input / 100 % 10]++;
    usedNums[input / 10 % 10]++;
    usedNums[input % 10]++;

    for (int i = 0; i < 10; i++) {
        if (usedNums[i] > 1) return ERR_REPEATING_DIGITS;
    }

    num[0] = input / 1000;
    num[1] = input / 100 % 10;
    num[2] = input / 10 % 10;
    num[3] = input % 10;

    return ERR_OK;
}

void generateCandidates() {
    for (int a = 1; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            if (b != a) {
                for (int c = 0; c <= 9; c++) {
                    if (c != a && c != b) {
                        for (int d = 0; d <= 9; d++) {
                            if (d != a && d != b && d != c) {
                                candidates[candidateCount][0] = a;
                                candidates[candidateCount][1] = b;
                                candidates[candidateCount][2] = c;
                                candidates[candidateCount][3] = d;
                                candidateCount++;
                            }
                        }
                    }
                }
            }
        }
    }
}

// Computer tries to guess
int8_t computerTurn(uint8_t compGuess[]) {
    uint8_t bulls = 0, cows = 0;

    printf("Computer guess: %d%d%d%d\n", compGuess[0], compGuess[1], compGuess[2], compGuess[3]);
    do {
        printf("Bulls: ");
        if (scanf("%hhd", &bulls) == 1) break;
        printf("Invalid input\n");
    } while (1);

    do {
        printf("Cows: ");
        if (scanf("%hhd", &cows) == 1) break;
        printf("Invalid input\n");
    } while (1);

    if (bulls == 4) {
        return GAME_WON_COMP;
    }

    int new_count = 0;
    for (int i = 0; i < candidateCount; i++) {
        uint8_t b = 0, c = 0;
        computeBullsAndCows(candidates[i], compGuess, &b, &c);
        if (b == bulls && c == cows) {
            for (int k = 0; k < PLAY_NUM_SIZE; k++) {
                candidates[new_count][k] = candidates[i][k];
            }
            new_count++;
        }
    }
    candidateCount = new_count;

    if (candidateCount == 0) return GAME_CHEAT_PLAYER;

    return GAME_WON_NOT;
}

// Player tries to guess
int8_t playerTurn(uint8_t compNum[]) {
    int32_t userInput;
    uint8_t inputNum[4] = {0};

    do {
        if (scanf("%d", &userInput) != 1) {
            printf("Invalid input\n");
            continue;
        }

        const int8_t parseErrorCode = parseInputNum(userInput, inputNum);

        if (parseErrorCode == ERR_OK) {
            break;
        }
        userErrorMessage(parseErrorCode);
    } while (1);

    uint8_t bulls = 0, cows = 0;
    computeBullsAndCows(inputNum, compNum, &bulls, &cows);
    printf("Bulls: %d\nCows: %d\n\n", bulls, cows);
    if (bulls == 4) {
        return GAME_WON_PLAYER;
    }

    return GAME_WON_NOT;
}


int main() {
    srand(time(NULL));

    int wantedRounds = 0, compWin = 0, playerWin = 0;
    printf("How many rounds ");
    scanf("%d", &wantedRounds);

    for (int round = 0; round < wantedRounds; round++) {
        uint8_t compNum[4] = {0};
        generateNumber(compNum);

        candidateCount = 0;
        generateCandidates();


        do {
            uint8_t compGuess[4] = {
                candidates[0][0],
                candidates[0][1],
                candidates[0][2],
                candidates[0][3]
            };

            printf("\n%d%d%d%d\n", compGuess[0], compGuess[1], compGuess[2], compGuess[3]);

            printf("Computer turn\n");
            const int8_t resultComp = computerTurn(compGuess);
            if (resultComp == GAME_WON_COMP) {
                printf("Computer wins\n");
                compWin++;
            }

            if (resultComp == GAME_CHEAT_PLAYER) {
                printf("Player cheated\nDeduct one point\n");
                playerWin--;
            }

            printf("Player turn\n");
            int8_t resultPlayer = playerTurn(compNum);
            if (resultPlayer == GAME_WON_PLAYER) {
                printf("Player wins\n");
                playerWin++;
            }
            if (resultComp != GAME_WON_NOT || resultPlayer != GAME_WON_NOT) {
                printf("Round completed\n");
                break;
            }
        } while (1);
    }

    printf("Rounds won\nComputer: %d\nPlayer: %d\n", compWin, playerWin);

    return 0;
}

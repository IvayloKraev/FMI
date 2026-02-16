#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 1000

#define ERR_REACH_MAX_DEPTH (-1)

int nextInSequence(int a) {
    int next = 0;

    while (a != 0) {
        next += (a % 10) * (a % 10);
        a /= 10;
    }

    return next;
}


void generateSums(int *sums, int a) {
    assert(sums);
    sums[0] = a;

    for (int i = 1; i < MAX_DEPTH; i++) {
        a = nextInSequence(a);
        sums[i] = sums[i-1] + a;
    }
}

int findKLower(const int * const sum, int A, int left, int right) {
    if (right == left)  return left;

    const int middle = left + (right - left) / 2;
    if (sum[middle] >= A) {
        return findKLower(sum, A, left, middle);
    }
    return findKLower(sum, A, middle + 1, right);
}

int findK(const int * const sum, int A) {
    assert(sum);
    if (A <= sum[0]) return 0;
    if (A > sum[MAX_DEPTH - 1]) return -1;
    return findKLower(sum, A, 0, MAX_DEPTH - 1);
}

int main() {
    int a;
    if (scanf("%d", &a) != 1) {
        return -1;
    }

    int *sums = calloc(MAX_DEPTH + 1, sizeof(int));
    if (sums == NULL) {
        free(sums);
        return -1;
    }

    generateSums(sums, a);

    int A;
    while (scanf("%d", &A) == 1 && A >= 0) {
        printf("   ");
        printf("%d\n", findK(sums, A));
    }

    free(sums);
    return 0;
}

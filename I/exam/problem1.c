#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int divisible(int a, int b) {
    return a % b == 0 || b % a == 0;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1 || N < 1) {
        return 1;
    }

    int *nums = calloc(N, sizeof(int));
    if (!nums) return 1;


    for (int i = 0; i < N; i++) {
        if (scanf("%d", &nums[i]) != 1 || nums[i] < 1) {
            free(nums);
            return 1;
        }
    }

    int *newNums = calloc(N * 2, sizeof(int));
    if (!newNums) {
        free(nums);
        return 1;
    }
    newNums[0] = nums[0];
    int j = 1;

    for (int i = 1; i < N;) {
        if (divisible(nums[i - 1], nums[i])) {
            newNums[j++] = nums[i++];
            continue;
        }

        if (i < N - 1 && divisible( nums[i], nums[i+1])) {
            newNums[j++] = nums[i++];
            continue;
        }
        newNums[j++] = gcd(nums[i], nums[i - 1]);
        newNums[j++] = nums[i++];
    }

    int *newNumsTemp = realloc(newNums, j * sizeof(int));
    if (!newNumsTemp) {
        free(nums);
        free(newNums);
        return 1;
    }
    newNums = newNumsTemp;

    for (int i = 0; i < j; i++) {
        printf("%d ", newNums[i]);
    }

    free(nums);
    free(newNums);

    return 0;
}

#include <stdio.h>

void subsetToTotalRec(int *set, size_t k, int total, size_t startPoint, size_t *subsetNum, int sum) {
    if (sum == total) {
        ++(*subsetNum);
        return;
    }
    if (sum > total) {
        return;
    }

    for (size_t i = startPoint; i < k; i++) {
        subsetToTotalRec(set, k, total, i + 1, subsetNum, sum + set[i]);
    }
}

size_t subsetToTotal(int *set, size_t k, int total) {
    size_t subsetNum = 0;

    subsetToTotalRec(set, k, total, 0, &subsetNum, 0);

    return subsetNum;
}

// input {a} : a > 0
int main() {
    int set[] = {1, 2, 3, 4, 5}, setLen = 5;
    size_t n = subsetToTotal(set, setLen, 100);
    printf("%d\n", n);
    return 0;
}

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequenceRecursion(char **words, int n, int pos, int *used, char **order) {
    if (pos == n) return 1;

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;

        if (pos == 0 || order[pos - 1][strlen(order[pos-1]) - 1] == words[i][0]) {
            used[i] = 1;
            order[pos] = words[i];

            if (sequenceRecursion(words, n, pos + 1, used, order)) return 1;

            used[i] = 0;
        }
    }

    return 0;
}

int sequence(char **words, int n, char **order) {
    assert(n > 0);
    assert(words != NULL);
    assert(order != NULL);

    int *used = calloc(n, sizeof(int));
    if (!used) {
        return -1;
    }

    int result = sequenceRecursion(words, n,0, used, order);

    free(used);

    return result;
}

int main() {
    char *words[] = {"abc", "cde", "cbd", "ecc"};
    int n = 4;

    char *order[4];

    if (sequence(words, n, order)) {
        for (int i = 0; i < n; i++) printf("%s ", order[i]);
        printf("\n");
    } else {
        printf("No solution\n");
    }
    return 0;

}
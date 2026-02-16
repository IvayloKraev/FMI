

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int squareFree(int a) {
    for (int i = 2; i * i < a; i++)
        if (a % (i*i) == 0)
            return 0;
    return 1;
}

int getSquareFreeColumns(int *matrix, int cols, int rows, int *squareFreeColumn) {
    assert(matrix);
    assert(squareFreeColumn);

#define MATRIX(i, j) matrix[i * cols + j]

    for (int i = 0; i < cols; i++) {
        int squareFreeCurr = 1;
        for (int j = 0; j < rows; j++) {
            if (squareFree(MATRIX(j, i))) {
                squareFreeCurr = 0;
                break;
            }
        }
        squareFreeColumn[i] = squareFreeCurr;
    }
    return 1;
}

int removeCols(int ***matrix, int *cols, int rows, int *removeCols) {
    assert(matrix);
    assert(removeCols);


    for (int i = 0; i < rows; i++) {
        int k = 0;
        for (int j = 0; j < *cols; j++) {
            if (!removeCols[j]) {
                (*matrix)[i][k++] = (*matrix)[i][j];
            }
        }

        /* shrink row */
        int *tmp = realloc((*matrix)[i], newCols * sizeof(int));
        if (tmp != NULL) {
            (*matrix)[i] = tmp;
        }
    }

}

int filterMatrix(int *matrix, int cols, int rows) {
    assert(matrix);


#define MATRIX(i, j) matrix[i * M + j]
    int *squareFreeColumn = calloc(cols, sizeof(int));
    if (squareFreeColumn) {
        return -1;
    }

    getSquareFreeColumns(matrix, cols, rows, squareFreeColumn);

    for

}

int main() {
    int N,M;
    if (scanf("%d %d",&N,&M) != 2 || N < 1 || M < 1) return 1;

    // int[N][M]
    int *matrix = calloc(N * M, sizeof(int));



    return 0;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_OK                  (-100)
#define ERR_INVALID_PARAMETER   (-101)
#define ERR_EMPTY_IMAGE         (-102)

int crop(int32_t **image, int *w, int *h, const int background) {
    if (!image || !*image || !w || !h || *w <= 0 || *h <= 0) { return ERR_INVALID_PARAMETER; }
    int startRow = *h, startCol = *w, endRow = -1, endCol = -1;

    for (int r = 0; r < *h; r++) {
        for (int c = 0; c < *w; c++) {
            if ((*image)[r * *w + c] != background) {
                if (r < startRow) startRow = r;
                if (r > endRow) endRow = r;
                if (c < startCol) startCol = c;
                if (c > endCol) endCol = c;
            }
        }
    }

    const int newW = endCol - startCol;
    const int newH = endRow - startRow;

    // The infamous printf() problem
    //
    // printf(" ");
    //
    // int32_t *newImage = calloc(newW * newH, sizeof(int32_t));
    // if (!newImage) {
    //     free(newImage);
    //     return -1;
    // }
    //
    //
    // for (int i = startRow; i <= endRow; i++) {
    //     for (int j = startCol; j <= endCol; j++) {
    //         newImage[(i - startRow) * (endCol - 1) + (j - startCol)] = (*image)[i * *w + j];
    //     }
    // }
    //
    // *w = newW;
    // *h = newH;
    //
    // free(*image);
    // *image = newImage;

    for (int i = 0; i < newH; i++) {
        for (int j = 0; j < newW; j++) {
            (*image)[i * newW + j] =
                (*image)[(startRow + i) * (*w) + (startCol + j)];
        }
    }

    int32_t *shrunk = (int32_t *)realloc(image, (size_t)newW * (size_t)newH * sizeof(int32_t));
    if (shrunk) {
        *image = shrunk;
    }
    *w = newW;
    *h = newH;

    return ERR_OK;
}

void printImage(int32_t *image, const int w, const int h) {
    if (!image) { return; }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("%d ", image[i * w + j]);
        }
        printf("\n");
    }
}


int main() {
    int background;
    if (scanf("%d", &background) != 1) { return 1; }

    int w, h;
    if (scanf("%d %d", &w, &h) != 2 || w < 0 || h < 0) { return 1; }

    int32_t *image = calloc(w * h, sizeof(int32_t));
    if (!image) { return 1; }

    for (int i = 0; i < w * h; i++) {
        if (scanf("%d", &image[i]) != 1) {
            free(image);
            return 1;
        }
    }

    if (crop(&image, &w, &h, background) != ERR_OK) {
        free(image);
        return 1;
    }

    printImage(image, w + 1, h + 1);

    //free(image);
    return 0;
}

#include <stdio.h>

typedef struct {
    float x;
    float y;
} point_t;

typedef int(optionFn_t)(point_t);

int optionA(point_t p);
int optionB(point_t p);
int optionC(point_t p);
int optionD(point_t p);

// Putting the needed functions in array for O(1) access time and no jump-like behaviour in the executable
optionFn_t *options[4] = {optionA, optionB, optionC, optionD};

void p1(void) {
    point_t point;
    scanf("%f %f", &point.x, &point.y);

    int option = 0;
    scanf("%d", &option);

    // The option like function could return any number, so I use (!!) to stabilize it to bool values
    const int inBoundaries = !!options[option - 1](point);

    printf("%d\n", inBoundaries);
}

int optionA(point_t p) {
    return (p.x >= -1 && p.x <= 1) && (p.y >= -1 && p.y <= 1);
}
int optionB(point_t p) {
    return (p.x >= 1 && p.x <= 2) && (p.y >= 1 && p.y <= 2);
}
int optionC(point_t p) {
    point_t center = {1, 1};
    float distX = p.x - center.x;
    float distY = p.y - center.y;
    return (distX*distX + distY*distY) <= 1; // Instead sqrt I just set the wanted radius to the power of 2
}

int optionD(point_t p) {
    int inBig, inSmallAdd, outSmallSub;

    {
        point_t centerBig = {0, 0};
        const float distX = p.x - centerBig.x;
        const float distY = p.y - centerBig.y;
        inBig = (p.y > 0) && (distX*distX + distY*distY) <= 4;
    }

    {
        point_t centerSmallAdd = {-1, 0};
        const float distX = p.x - centerSmallAdd.x;
        const float distY = p.y - centerSmallAdd.y;
        inSmallAdd = (distX*distX + distY*distY) <= 1;

    }

    {
        point_t centerSmallSub = {1, 0};
        const float distX = p.x - centerSmallSub.x;
        const float distY = p.y - centerSmallSub.y;
        outSmallSub = (distX*distX + distY*distY) >= 1;
    }

    return (inBig || inSmallAdd) && outSmallSub;
}

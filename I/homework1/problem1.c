#include "stdio.h"

#define EPS 1e-9

int main() {
    float xA, yA, xB, yB, xC, yC, xD, yD;
    scanf("%f %f", &xA, &yA);
    scanf("%f %f", &xB, &yB);
    scanf("%f %f", &xC, &yC);
    scanf("%f %f", &xD, &yD);

    const float ABx = xB - xA, ABy = yB - yA,
            BCx = xC - xB, BCy = yC - yB,
            CDx = xD - xC, CDy = yD - yC,
            ADx = xD - xA, ADy = yD - yA;

    const float sideABSq = ABx * ABx + ABy * ABy,
            sideBCSq = BCx * BCx + BCy * BCy,
            sideCDSq = CDx * CDx + CDy * CDy,
            sideADSq = ADx * ADx + ADy * ADy;

    if (!((sideABSq - sideBCSq < EPS && sideBCSq - sideABSq < EPS) &&
          (sideBCSq - sideCDSq < EPS && sideCDSq - sideBCSq < EPS) &&
          (sideCDSq - sideADSq < EPS && sideADSq - sideCDSq < EPS))) {
        printf("Sides not equal\n");
        return 0;
    }

    const float dotAB_BC = ABx * BCx + ABy * BCy,
            dotBC_CD = BCx * CDx + BCy * CDy,
            dotCD_DA = CDx * ADx + CDy * ADy,
            dotDA_AB = ADx * ABx + ADy * ABy;

    if (!((dotAB_BC < EPS && -dotAB_BC < EPS) &&
          (dotBC_CD < EPS && -dotBC_CD < EPS) &&
          (dotCD_DA < EPS && -dotCD_DA < EPS) &&
          (dotDA_AB < EPS && -dotDA_AB < EPS))) {
        printf("Sides not perpendicular\n");
        return 0;
    }

    const float xO = (xA + xC) / 2.0f,
            yO = (yA + yC) / 2.0f;

    const float rSmallSq = sideABSq / 4.0f,
            rBigSq = sideABSq / 2.0f;

    float xP, yP;
    scanf("%f %f", &xP, &yP);

    const float OPx = xP - xO, OPy = yP - yO,
            APx = xP - xA, APy = yP - yA;

    const float OPsq = OPx * OPx + OPy * OPy;

    if (OPsq < rSmallSq - EPS || OPsq > rBigSq + EPS) {
        printf("The point is outside the ring\n");
        return 0;
    }

    printf("The point is inside the ring\n");


    const float u = (APx * ADy - APy * ADx) / (ABx * ADy - ABy * ADx),
            v = (ABx * APy - ABy * APx) / (ABx * ADy - ABy * ADx);

    if (u >= -EPS && u <= 1.0f + EPS &&
        v >= -EPS && v <= 1.0f + EPS) {
        printf("In the square\n");
    } else {
        printf("Outside the square\n");
    }

    return 0;
}

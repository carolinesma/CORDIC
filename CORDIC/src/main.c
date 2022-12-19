#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fix_point.h"
#include "cordic.h"

#define ANGLE_30_RAD (float)0.5236
#define TAM 5

int main(void)
{

    float theta[TAM] = {-0.861879263113481, 5.16034986349644,-3.99802815440608,-2.96814008901540,-4.45428854082928};
    float x[TAM] = {-0.861879263113481, 5.16034986349644,-3.99802815440608,-2.96814008901540,-4.45428854082928};
    float y[TAM] = {4.2816,-3.0878, 3.9494,-3.2230,5.3943};
    float a[TAM] = {2,-1,1.5,0.4,-0.2};
    float b[TAM] = {2,0.3,0.5,0.2,-0.01};
    float sin, cos, rx, ry, mag, phase, c;
    char I,i;
    short R;


    I = I_FIX;

    printf("***************************************\n");
    printf("Sin e Cossin\n");
    printf("theta / seno / cosseno\n");
    for(i=0;i<TAM;i++)
    {
        cossin(theta[i],&sin,&cos,I);
        printf("%f %f  %f \n", theta[i], sin, cos);
    }

    printf("***************************************\n");
    printf("Polar para Cartesian\n");
    printf("theta / R / x / y\n");
    R = 1;
    for(i=0;i<TAM;i++)
    {
        pol2ret(theta[i],R,&rx,&ry,I);
        printf("%f %d %f %f \n", theta, R, rx, ry);
    }

    printf("***************************************\n");
    printf("Cartesian para Polar\n");
    printf("x / y / mag / phase\n");
    for(i=0;i<TAM;i++)
    {
        ret2pol(x[i], y[i], &mag, &phase, I);
        printf("%f  %f %f  %f \n", x[i], y[i], mag, phase);
    }

    printf("***************************************\n");
    printf("Multiply\n");
    printf("a / b / c\n");
    for(i=0;i<TAM;i++)
    {
        multiply(a[i], b[i], &c, I);
        printf("%f %f %f \n", a[i], b[i], c);
    }
    printf("***************************************\n");
    printf("Divide\n");
    printf("a / b / c\n");
    for(i=0;i<TAM;i++)
    {
     divide(a[i], b[i], &c, I);
     printf("%f %f %f \n", a[i], b[i], c);
    }

}

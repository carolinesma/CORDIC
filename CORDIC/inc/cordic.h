#ifndef INC_CORDIC_H_
#define INC_CORDIC_H_

#define TAM_TABLE    13
#define PI          (float)3.141592653589793
#define HALF_PI     (float)1.570796326794897
#define K           (short)2487 //K = 0.60725293 em Q3,12
#define I_FIX       (char)39

float angle_shift (float alpha, float beta);
//void rotation(short *x, short *y, short *z, short m, short R);
void cossin(float theta, float *rsin, float *rcos, char I );
void pol2ret(float theta, short R, float *rx, float *ry,  char I);
void ret2pol(float cx, float cy, float *mag, float *phase, char I);
void multiply(float a, float b, float *c, char I);
void divide(float a, float b, float *c, char I);


#endif /* INC_CORDIC_H_ */

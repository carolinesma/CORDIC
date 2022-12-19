#include "stdio.h"
#include <math.h>
#include "fix_point.h"
#include "cordic.h"


short arctan_table[TAM_TABLE] = {3217,1899,1003,509,256,128,64,32,16,8,4,2,1};


float angle_shift (float alpha, float beta)
{
    float gamma;

    if ( alpha < beta )
    {
    gamma = beta - fmod ( beta - alpha, 2.0 * PI ) + 2.0 * PI;
    }
    else
    {
    gamma = beta + fmod ( alpha - beta, 2.0 * PI );
    }

    return gamma;
}

void cossin(float theta, float *sin, float *cos, char I )
{
    short z, x, y, xtemp;
    char i, sign_factor;

    //converte para para [pi;-pi]
    theta = angle_shift(theta, -PI);
    //converte para [-pi/2, pi/2]
    if (theta < -HALF_PI)
    {
        theta = theta + PI;
        sign_factor = -1;
    }
    else if(theta > HALF_PI)
    {
        theta = theta - PI;
        sign_factor = -1;
    }
    else
    {
        sign_factor = +1;
    }

    x = K; //formato Q3,12
    y = 0;
    z = toQ12(theta); //formato Q3,12

    for(i=0;i<=I;i++)
    {
        if (z > 0)
        {
            xtemp = x - (y >> i);
            y = y + (x >> i);
            x=xtemp;
            if (i <TAM_TABLE)
            {
                z = z - arctan_table[i];
            }
            else
            {
                z = z - arctan_table[TAM_TABLE-1];
            }
        }
        else
        {
            xtemp = x + (y >> i);
            y = y - (x >> i);
            x=xtemp;
            if (i <TAM_TABLE)
            {
                z = z + arctan_table[i];
            }
            else
            {
                z = z + arctan_table[TAM_TABLE-1];
            }
        }
    }


    if (sign_factor == -1)
    {
        x = -x;
        y = -y;
    }

    *sin = Q12toFloat(y);
    *cos = Q12toFloat(x);
}

void pol2ret(float theta, short R, float *rx, float *ry,  char I)
{
    short z, x, y, xtemp;
    char i, sign_factor;

    //converte para para [pi;-pi]
    theta = angle_shift(theta, -PI);
    //converte para [-pi/2, pi/2]
    if (theta < -HALF_PI)
    {
        theta = theta + PI;
        sign_factor = -1;
    }
    else if(theta > HALF_PI)
    {
        theta = theta - PI;
        sign_factor = -1;
    }
    else
    {
        sign_factor = +1;
    }

    z = toQ12(theta);
    R = toQ12(R);
    x = divQ12(K,R);
    y = 0;

    for(i=0;i<=I;i++)
    {
        if (z > 0)
        {
            xtemp = x - (y >> i);
            y = y + (x >> i);
            x=xtemp;
            if (i <TAM_TABLE)
            {
                z = z - arctan_table[i];
            }
            else
            {
                z = z - arctan_table[TAM_TABLE-1];
            }
        }
        else
        {
            xtemp = x + (y >> i);
            y = y - (x >> i);
            x=xtemp;
            if (i <TAM_TABLE)
            {
                z = z + arctan_table[i];
            }
            else
            {
                z = z + arctan_table[TAM_TABLE-1];
            }
        }
    }


    if (sign_factor == -1)
    {
        x = -x;
        y = -y;
    }

    *ry = Q12toFloat(y);
    *rx = Q12toFloat(x);
}

void ret2pol(float cx, float cy, float *mag, float *phase, char I)
{
    short z, x, y, xtemp;
    char i;

    if (cx < 0)
    {
       xtemp = cx;
       if (cy > 0.0)
       {
           cx = cy;
           cy = -xtemp;
           z = -HALF_PI;
       }
       else
       {
           cx = -cy;
           cy= xtemp;
           z = HALF_PI;
       }
    }
    else
    {
          z = 0.0;
    }

    z = toQ12(z);;
    x = toQ12(cx);
    y = toQ12(cy);

    for(i=0;i<=I;i++)
    {
        if (y < 0)
        {
            xtemp = x - (y >> i);
            y = y + (x >> i);
            x=xtemp;
            if (i <TAM_TABLE)
            {
                z = z - arctan_table[i];
            }
            else
            {
                z = z - arctan_table[TAM_TABLE-1];
            }
        }
        else
        {
            xtemp = x + (y >> i);
            y = y - (x >> i);
            x=xtemp;
            if (i <TAM_TABLE)
            {
                z = z + arctan_table[i];
            }
            else
            {
                z = z + arctan_table[TAM_TABLE-1];
            }
        }
    }

    //z = sign_factor * z;
    xtemp = mulQ12(x,K);
    *mag = Q12toFloat(xtemp);
    *phase = Q12toFloat(z);
}

void multiply(float a, float b, float *c, char I)
{

    short z, x, y, d, ytemp;
    char i;

    x = toQ12(a);
    y = 0;
    z = toQ12(b);
    d=toQ12(1);

    for(i=0;i<=I;i++)
    {
        if (z < 0)
        {
            ytemp = y - (x >> i);
            y = ytemp;
            z = z + (d>>i);
        }
        else
        {
            ytemp = y + (x >> i);
            y = ytemp;
            z = z - (d>>i);
        }
    }

    *c = Q12toFloat(y);
}

void divide(float a, float b, float *c, char I)
{

    short z, x, y, d, ytemp;
    char i;

    x = toQ12(b);
    y = toQ12(a);
    z = 0;
    d=toQ12(1);

    for(i=0;i<=I;i++)
    {
        if (y > 0)
        {
            ytemp = y - (x >> i);
            y = ytemp;
            z = z + (d>>i);
        }
        else
        {
            ytemp = y + (x >> i);
            y = ytemp;
            z = z - (d>>i);
        }
    }

    *c = Q12toFloat(z);
}

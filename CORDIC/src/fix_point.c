#include "stdio.h"
#include <math.h>
#include "fix_point.h"

short toQ12(float n)
{
    short result = 0;

    result = (short)(n*(1<<12));

    return result;
}

float Q12toFloat(short n)
{
    float result = 0;

    result = n*1.0/(1<<12);

    return result;
}

short toQ15(float n)
{
    short result = 0;

    result = (short)(n*(1<<15));

    return result;
}

float Q15toFloat(short n)
{
    float result = 0;

    result = n* 1.0/(1<<15);

    return result;
}

short divQ12(short a, short b)
{
    short min, c;
    long temp;

    min = -32768;

    if  (b == 0)
    {
        return min;
    }

    temp = (long)a;
    temp =  (temp<<12);
    temp =  temp + (b>>1);
    temp = temp/(long)b;
    c = (short)temp;

    return c;
}

short mulQ12(short a, short b)
{
    short min, max, c;
    long temp;

    max = 32767;
    min = -32768;

    if  (b == 0)
    {
        return min;
    }

    temp = (long)a * (long)b;
    temp = temp + (1 << 12);
    temp = temp >> 12;
    c = (short)temp;

    if (temp > max)
    {
        temp = max;
    }
    if (temp < min)
    {
        temp = min;
    }

    return c;
}

#include<stdio.h>
#include<stdlib.h>
#include"math/MathFunction.h"

int main(int argc,char *argv[])
{
    if(argc<3)
    {
        printf("参数错误\n");
        return 1;
    }
    double a=atof(argv[1]);
    double b=atof(argv[2]);
    double ret=a+b;
    printf("%g+%g=%g\n",a,b,ret);
    return 0;
}

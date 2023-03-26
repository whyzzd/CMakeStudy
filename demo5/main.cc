#include<stdio.h>
#include<stdlib.h>
#include"build/config.h"

#ifdef USE_MYMATH
  #include "math/MathFunction.h"
#else
  #include <math.h>
#endif
int main(int argc,char *argv[])
{
    if(argc<3)
    {
        printf("参数错误\n");
        return 1;
    }
    double a=atof(argv[1]);
    int b=atoi(argv[2]);
#ifdef USE_MYMATH
    printf("Now we use our own Math library. \n");
    double ret = powFun(a, b);
#else
    printf("Now we use the standard library. \n");
    double ret = pow(a, b);
#endif
    printf("%g^%d=%g\n",a,b,ret);
    return 0;
}

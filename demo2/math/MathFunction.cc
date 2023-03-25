#include"MathFunction.h"
double powFun(double a,int b)
{
    int result = a;
    int i;

    if (b == 0) {
        return 1;
    }

    for(i = 1; i < b; ++i){
        result = result * a;
    }

    return result;
}

#include <stdio.h>
int main(int argc, char const *argv[])
{
int num1 = 10;
int num2 = 3;
float result1;
int result2;
// int -> float にキャストして除算
result1 = (float)num1 / num2;
printf("result1: %f\n", result1);
// float -> int にキャストして代⼊
result2 = (int)result1;
rintf("result2: %d\n", result2);
return 0;
}
#include <stdio.h>
int main(int argc, char const *argv[])
{
char chr = -100;
unsigned char unchr;
unchr = (unsigned char)chr;
printf("unsigned char unchr : %u\n", unchr);
return 0;
}
#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void){
    for(int i = 1; i < 10; i++){
        double srt = sqrt(i);
        int intValOfSqrt = srt;
        printf("Square root of %i is %f\n", i, srt);
        if (srt == intValOfSqrt) {
            printf("%i is a perfect square\n", i);
        }
    }
}
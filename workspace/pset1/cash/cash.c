#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {
    float input = 0.0;

    do {
        input = get_float("Change owed: ");
    } while(input < 0);

    int change = round(input * 100);
    printf("Change = %i\n", change);

    int numQuarters = 0;
    int numDimes = 0;
    int numNickels = 0;
    int numPennies = 0;
    if(change / 25 > 0){
        numQuarters = change / 25;
        change = change % 25;
    }
    if(change / 10 > 0){
        numDimes = change / 10;
        change = change % 10;
    }
    if(change / 5 > 0){
        numNickels = change / 5;
        change = change % 5;
    }
    numPennies = change;

    printf("%i\n", numQuarters + numDimes + numNickels + numPennies);
}
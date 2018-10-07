#include <stdio.h>
#include <cs50.h>

int main(void){
    int height = 0;
    do{
        height = get_int("Height: ");
    }
    while(height < 0 || height > 23);


    int count = 1;
    int count2 = 1;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < height - count; i++){
            printf(" ");
        }
        count++;
        for(int k = 0; k < count - 1; k++){
            printf("#");
        }
        printf(" ");
        printf(" ");
        for(int l = 0; l < count2; l++){
            printf("#");
        }
        count2++;
        printf("\n");
    }
}


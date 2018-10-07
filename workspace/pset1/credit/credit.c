#include <stdio.h>
#include <cs50.h>


bool isValidChecksum(int ccdigits[], int length);

int main(void) {
    long long input = get_long_long("Number: ");
    int arr[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    while(input > 9){
        arr[i] = input % 10;
        input = input / 10;
        i++;
    }
    arr[i] = input;
    int length = i + 1;
    if(length != 13 && length != 15 && length != 16){
        printf("INVALID\n");
        return 0;
    }

    int ccdigits[length];
    int k = 0;
    for(int j = length - 1; j >= 0; j--) {
        ccdigits[k] = arr[j];
        k++;
    }
    bool validChecksum = isValidChecksum(ccdigits, length);
    if (!validChecksum) {
        printf("INVALID\n");
        return 0;
    }
    if (length == 15 && ccdigits[0] == 3 && (ccdigits[1] == 4 || ccdigits[1] == 7)) {
        printf("AMEX\n");
        return 0;
    }

    if (length == 13 && ccdigits[0] == 4) {
        printf("VISA\n");
        return 0;
    }
    if (length == 16){
        if(ccdigits[0] == 4){
            printf("VISA\n");
            return 0;
        }
        if(ccdigits[0] == 5 &&
            (ccdigits[1] == 1 ||
                ccdigits[1] == 2 ||
                ccdigits[1] == 3 ||
                ccdigits[1] == 4 ||
                ccdigits[1] == 5)) {
            printf("MASTERCARD\n");
            return 0;
        }
    }
    printf("INVALID\n");
}

bool isValidChecksum(int ccdigits[], int length) {
    int sum = 0;
    int product = 0;
    for(int i = length - 2; i >= 0; i -= 2){
        product = ccdigits[i] * 2;
        if(product > 9){
            sum = sum + (product % 10);
            sum = sum + (product / 10);
        } else {
            sum = sum + product;
        }
    }
    for(int i = length - 1; i >= 0; i -= 2){
        sum = sum + ccdigits[i];
    }
    if(sum % 10 == 0){
        return true;
    }
    return false;
}
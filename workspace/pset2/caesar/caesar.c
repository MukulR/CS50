#include <stdio.h>
#include <cs50.h>
#include <math.h>

void modifymsg(char msg[], int k);
bool isLower(char c);

int main(int argc, string argv[]){
    if(argc != 2){
        printf("Error: Expected only 1 parameter.\n");
        return 1;
    }
    int i = 0;
    int k = atoi(argv[1]);
    string msg = get_string("plaintext: ");

    modifymsg(msg, k);
    printf("ciphertext: ");
    while(msg[i] != '\0'){
        printf("%c", msg[i]);
        i++;
    }
    printf("\n");
}

void modifymsg(char msg[], int k){
    int i = 0;
    while(msg[i] != '\0'){
        if((msg[i] >= 'A' && msg[i] <= 'Z') || (msg[i] >= 'a' && msg[i] <= 'z')){
            if(isLower(msg[i])){
                msg[i] = (msg[i] - 97 + k) % 26 + 97;
            } else{
                msg[i] = (msg[i] - 65 + k) % 26 + 65;
            }
        }
        i++;
    }
}

bool isLower(char c){
    if(c >= 'a' && c <= 'z'){
        return true;
    }
    return false;
}
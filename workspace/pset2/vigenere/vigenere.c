#include <stdio.h>
#include <cs50.h>
#include <math.h>

void modifymsg(string msg, string keyword);
bool isLower(char c);

int main(int argc, string argv[]){
    if(argc != 2){
        printf("Error: Expected only 1 keyword.\n");
        return 1;
    }
    string keyword = argv[1];
    int i = 0;
    while(keyword[i] != '\0'){
        if(!((keyword[i] >= 'a' && keyword[i] <= 'z') || (keyword[i] >= 'A' && keyword[i] <= 'Z'))){
            printf("Error: Expected only alphabets in keyword.\n");
            return 1;
        }
        i++;
    }
    i = 0;
    string msg = get_string("plaintext: ");

    modifymsg(msg, keyword);
    printf("ciphertext: ");
    while(msg[i] != '\0'){
        printf("%c", msg[i]);
        i++;
    }
    printf("\n");
}

void modifymsg(string msg, string keyword){
    printf("msg = %s\n", msg);
    printf("keyword = %s\n", keyword);
    int j = 0;
    int i = 0;
    while(msg[i] != '\0'){
        if((msg[i] >= 'A' && msg[i] <= 'Z') || (msg[i] >= 'a' && msg[i] <= 'z')){
            if(keyword[j] == '\0'){
                j = 0;
            }

            int k = 0;
            if(isLower(keyword[j])){
                k = keyword[j] - 97;
            } else{
                k = keyword[j] - 65;
            }

            if(isLower(msg[i])){
                msg[i] = (msg[i] - 97 + k) % 26 + 97;
            } else {
                msg[i] = (msg[i] - 65 + k) % 26 + 65;
            }
            j++;
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
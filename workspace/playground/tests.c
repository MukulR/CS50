#define _XOPEN_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <string.h>


int main(){
   string s = get_string("txt: ");
   printf("input string = %s\n", s);
   if(strcmp(s, "\0") == 0){
       printf("true\n");
    } else {
        printf("false\n");
    }
}


#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[]) {
    if (argc < 2) {
        // Nothing to change just print the message
    }
    printf("Number of commandline arguments are: %i\n", argc);
    printf("The second commandline argument is: %s\n", argv[1]);

    int k = atoi(argv[1]);
    printf("The integer value of second commandline argument is: %i\n", k);

}
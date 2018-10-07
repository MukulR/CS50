#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdio.h>





int frequency(string note)
{
    char noteval[2];
    noteval[0] = note[1];
    noteval[1] = '\0';
    int octave = atoi(noteval);
    int n = 12 * (octave - 4);
    return round(pow(2, n / 12) * 440);
}

int main(void){
    string s = get_string("blah: ");
    printf("%s: %i\n", s, frequency(s));
}
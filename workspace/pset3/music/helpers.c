    // Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>
#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    char number[2];
    number[0] = fraction[0];
    number[1] = '\0';

    int numerator = atoi(number);
    number[0] = fraction[2];
    int denominator = atoi(number);

    return (numerator * 8) / denominator;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char noteval[2];
    noteval[0] = note[1];
    noteval[1] = '\0';
    int octave = atoi(noteval);
    int n = 12 * (octave - 4);
    return round(pow(2, n / 12) * 440);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //get string returns [NULL, NULL] when no string entered.
    return (strcmp(s, "\0") == 0);
}

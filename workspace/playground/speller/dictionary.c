// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>

int wordcount = 0;
typedef struct TrieNode{
    char *word;
    struct TrieNode *triePtrs[27];
}TrieNode;

struct TrieNode *root = NULL;

void changeToLower(char *c){
    for(int i = 0; i < strlen(c); i++){
        c[i] = tolower(c[i]);
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    struct TrieNode *current = root;
    char *lower = (char *)malloc(1 + sizeof(char) * strlen(word));
    char c = word[0];
    int count = 0;
    while (c != '\0') {
        lower[count] = tolower(c);
        count++;
        c = word[count];
    }
    lower[count] = '\0';
    int index = 0;
    for(int i = 0; i < strlen(lower); i++){
        if(lower[i] == 39){
            index = 26;
        } else {
            index = lower[i] - 'a';
        }
        if(current->triePtrs[index] == NULL){
            return false;
        } else {
            current = current->triePtrs[index];
        }
    }
    if(current != NULL && strcmp(current->word, lower) == 0){
        return true;
    } else {
        return false;
    }
}

void addToTrie(char *word){
    struct TrieNode *current = root;
    char *lower = (char *)malloc(1 + sizeof(char) * strlen(word));
    char c = word[0];
    int count = 0;
    while (c != '\0') {
        lower[count] = tolower(c);
        count++;
        c = word[count];
    }
    lower[count] = '\0';
    int index = 0;
    for(int i = 0; i < strlen(lower); i++){
        if(lower[i] == 39){
            index = 26;
        } else {
            index = lower[i] - 'a';
        }
        if(current->triePtrs[index] == NULL){
            struct TrieNode *temp = (TrieNode *)malloc(sizeof(TrieNode));
            current->triePtrs[index] = temp;
            current = temp;
        } else {
            current = current->triePtrs[index];
        }
    }
    if(current != NULL){
        current->word = (char *)malloc(1 + sizeof(char) * strlen(lower));
        strcpy(current->word, lower);
    }
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if(inptr == NULL){
        printf("Could not open file\n");
        return false;
    }

    TrieNode *tn = (TrieNode*)malloc(sizeof(TrieNode));
    root = tn;
    char *word = (char *)malloc(46 * sizeof(char));
    while(fscanf(inptr, "%s", word) != EOF){
        addToTrie(word);
        wordcount++;
        free(word);
        word = (char *)malloc(46 * sizeof(char));
    }
    free(word);
    fclose(inptr);

    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    return false;
}

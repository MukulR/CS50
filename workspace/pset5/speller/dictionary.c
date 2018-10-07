// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>

const int HASHSIZE = 5000;

unsigned hash(const char *s);
void changeToLower(char *c);
void addToHashtable(char *word);

typedef struct WordNode{
    char *word;
    struct WordNode *next;
} WordNode;

WordNode *hashtable[HASHSIZE];
int wordcount = 0;

void changeToLower(char *c){
    for(int i = 0; i < strlen(c); i++){
        c[i] = tolower(c[i]);
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char *lower = (char *)malloc(1 + sizeof(char) * strlen(word));
    char c = word[0];
    int i = 0;
    while (c != '\0') {
        lower[i] = tolower(c);
        i++;
        c = word[i];
    }
    lower[i] = '\0';
    unsigned index = hash(lower);
    WordNode *current = hashtable[index];
    bool found = false;
    while(current != NULL){
        if(strcmp(lower, current->word) == 0){
            found = true;
            break;
        } else {
            current = current->next;
        }
    }
    free(lower);
    return found;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *inptr = fopen(dictionary, "r");
    if(inptr == NULL){
        printf("Could not open file\n");
        return false;
    }
    for(int i = 0; i < HASHSIZE; i++){
        hashtable[i] = NULL;
    }
    char *word = (char *)malloc(46 * sizeof(char));
    while(fscanf(inptr, "%s", word) != EOF){
        addToHashtable(word);
        wordcount++;
        free(word);
        word = (char *)malloc(46 * sizeof(char));
    }
    free(word);
    fclose(inptr);
    return true;
}

void addToHashtable(char *word){
    WordNode *wn = (WordNode*)malloc(sizeof(WordNode));
    wn->word = (char *)malloc(sizeof(char) * strlen(word));
    memcpy(wn->word, word, strlen(word));
    int index = hash(word);
    if(hashtable[index] == NULL){
        hashtable[index] = wn;
    } else {
        WordNode *tmp = hashtable[index];
        hashtable[index] = wn;
        wn->next = tmp;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < HASHSIZE; i++){
        if(hashtable[i] != NULL){
            WordNode *current = hashtable[i];
            WordNode *temp = NULL;
            while(current != NULL){
                temp = current->next;
                free(current->word);
                free(current);
                current = temp;
            }
        }
    }
    return true;
}


unsigned hash(const char *s){
    unsigned hashval;

    for(int i = 0; i < strlen(s); i++){
        hashval = s[i] + 7 * hashval;
    }
    return hashval % HASHSIZE;
}
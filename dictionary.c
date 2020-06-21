// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char modified_word[LENGTH+1];
    for(int i=0;i<LENGTH;i++)
    {
        modified_word[i]=tolower(word[i]);
    }
    int index=hash(modified_word);
    node *tmp=table[index];
    while(tmp!=NULL)
    {
        if(strcasecmp(tmp->word,modified_word)==0)
        {
            return true;
        }
        tmp=tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // https://github.com/andycloke/Harvard-CS50-Solutions/blob/master/pset5/speller/dictionary.c
    unsigned int hash = 0;
    for (int i=0, n=strlen(word); i<n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % N;
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    int word_count;
    FILE *file=fopen(dictionary,"r");
    if(file==NULL)
    {
        printf("dictionary cannot be opened for reading\n");
        return false;
    }
    char file_word[LENGTH+1];
    node *element=NULL;
    while(fscanf(file,"%s",file_word)!=EOF)
    {
        element=malloc(sizeof(node));
        if(element==NULL)
        {
            printf("there's no free space in memory\n");
            return false;
        }
        strcpy(element->word,file_word);
        int index=hash(file_word);
        element->next=table[index];
        table[index]=element;
    }
    fclose(file);
    return true;
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int word_counter=0;
    node *tmp=NULL;
    for(int i=0;i<N;i++)
    {
        tmp=table[i];
        while(tmp!=NULL)
        {
            word_counter++;
            tmp=tmp->next;
        }
    }
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *tmp=NULL;
    bool unloaded=false;
    for(int i=0;i<N;i++)
    {
        while(table[i]!=NULL)
        {
            tmp=table[i];
            table[i]=table[i]->next;
            free(tmp);
        }
        unloaded=true;
    }
    return unloaded;
}

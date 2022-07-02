// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <cs50.h>

#include "dictionary.h"
int countNumber = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);


    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {

        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;

}


// Hashes word to a number

unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    char dictword[LENGTH]; // LENGTH = 45



    for (int i = 0; i < 1; i++)
    {
        while (fscanf(dict, "%s", dictword) != EOF)
        {
            node *n = malloc(sizeof(node));

            if (n == NULL)
            {
                return false;
            }
            strcpy(n->word, dictword);
            int index = hash(dictword);
            n->next = table[index];

            table[index] = n;

            countNumber++;
        }
        fclose(dict);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (countNumber > 0)
    {
        return countNumber;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {

            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);

        }
        // If cursor is NULL
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}

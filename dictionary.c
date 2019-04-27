// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// amount words in dictionary
int amount_word = 0;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Allocate space for word - це моє
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return 1;
        }
        // Add word to list (замість "strcpy" можна використати цикл
    /*    for (int i = 0, j = strlen(word); i < j; i++)
        {
            n->word[i] = word[i];
        }
    */
        strcpy(n->word, word);
        amount_word++;
        n->next = NULL;
        if (hashtable[hash(word)])
        {
            for (node *ptr = hashtable[hash(word)]; ptr != NULL; ptr = ptr->next)
            {
                if (!ptr->next)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
        else
        {
            hashtable[hash(word)] = n;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (amount_word > 0)
    {
        return amount_word;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    if (strlen(word) < 46)
    {
        // виділяємо пам'ять для копіювання шуканого слова
        char *t = malloc((strlen(word) + 1) * sizeof(char));
        if (!t)
        {
            return false;
        }
        // копіюємо шукане слово
        strcpy(t, word);

        if (strlen(t) > 0)
        {
            // заносимо літери до нижнього регістру окрім апострофу
            for (int i = 0, n = strlen(t); i < n; i++)
            {
                if (isalpha(t[i]))
                {
                    t[i] = tolower(t[i]);
                }
                else
                {
                    t[i] = t[i];
                }
            }
        }
        // порівнюємо слово зі словником
        for (node *ptr = hashtable[hash(t)]; ptr != NULL; ptr = ptr->next)
        {
            if (strcmp(ptr->word, t) == 0)
            {
                free(t);
                return true;
            }
        }
        free(t);
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (amount_word > 0)
    {
        for (int i = 0; i < 26; i++)
        {
            node *ptr = hashtable[i];
            while (ptr != NULL)
            {
                node *next = ptr->next;
                free(ptr);
                ptr = next;
            }
        }
        return true;
    }
    return false;
}

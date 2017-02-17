/**
 * Implements a dictionary using a trie structure
 * By Kyap 2017
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

//create the structure for a node, which will form part of a trie
typedef struct node
{
    bool is_word;
    struct node *children[27]; //a struct node pointer named children which is an array of 27 elements
}
node;

//initialise the root node
node *root;

//initialise counter_nodes
int counter_nodes = 0;

//returns index of letter within the trie array
int GetIndex (c)
{
    if (c == '\'')
        return 26;
    else
        return tolower(c) % 'a';
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    //initialise cursor at root node...this seems familiar
    node *cursor = root;

    //for each letter in input word 
    for(int i = 0, n = strlen(word); i < n; i++) //OPTIMISE: can we use null terminator instead of string len
    {
        int index = GetIndex(word[i]);
        
        //if the next letter does not exist in our dictionary, then word is mispelt
        if (cursor->children[index] == NULL)
        {
            return 1;
        }
        
        //if next letter exists, follow it to the next node
        else if (cursor->children[index] != NULL)
        {
            cursor = cursor->children[index];
        }
    }
    
    //assuming we have reach End of input word and all letters exist
    //check if it is actually a word in the dictionary
    if (cursor->is_word == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //allocate space to root
    root = malloc(sizeof(node));
    
    // Set a pointer of type node called cursor to root
    node *cursor = root; 
    
    // try to open dictionary (location referenced in speller.c)
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        unload();
        return 1;
    }

    //for every dictionary word, iterate through the trie
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        //Get index of letter
        int index = GetIndex(c);
    
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            //does a node containing that letter exist?
            if (cursor->children[index] == NULL) //Conditional jump or move depends on uninitialised value(s)
            {
                //if it does not, create a new node
                cursor->children[index] = malloc(sizeof(node));
                
                //malloc error checking
                if (cursor == NULL)   
                {
                    printf("Error -- out of memory allocating new child node.\n");
                    return 1;
                }
                
                //and move cursor there
                cursor = cursor->children[index];
            }   
            //if it does exist
            else
            {
                //move cursor to that node
                cursor = cursor->children[index];
            }
            
        }    
        
        // if newline
        else if (c == '\n')
        {
            //then we've reached the end of a word
            cursor->is_word = true;
            
            //add to the word count
            counter_nodes ++;
            
            //set the cursor back to root
            cursor = root;
        }
        //if not an alphabetical character, apostrophe or newline
        else
        {
            printf("unrecognised character in dictionary text.\n");
            return 1;
        }
    }    
    //release the memory held by cursor
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //if dictionary is not loaded
    if (!&load)
    {
        return 1;
    }
    
    //else return number of nodes we counted in load
    else
    {
        return counter_nodes;
    }
}

/**
 * Helper function for unload - recursive free
 */
bool recursivefree (node *ptr)
    {
        for (int i = 0; i < 27; i++)
        {
            if (ptr->children[i] != NULL)
            {
                recursivefree (ptr->children[i]);
            }
        }
        free(ptr);
        return true;
    }
    
/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    if (recursivefree (root))
    {
        return 1;
    }
    
    return 0;
}

/**
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include "dictionary.h"

//create the structure for a node, which will form part of a trie
typedef struct node
{
    bool is_word;
    struct node *children[27]; //a struct node pointer named children which is an array of 27 elements
}
node;

//initialise the root node
node* root;

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
    // TODO
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //allocate space to root
    root = malloc(sizeof(node));
    
    // Set a pointer of type node called cursor to root
    node* cursor = root; 
    
    // Initialise counter of nodes
    int counter_nodes = 0; 
    
    // try to open dictionary
    char *dick = "~/workspace/pset5/speller/dictionaries/small.txt";  
    FILE *fp = fopen(dick, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dick);
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
            if (cursor->children[index] == NULL)
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
            printf("unrecognised character in dictionary text.\n");
            return 1;
        
    }    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}

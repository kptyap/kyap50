/*
-- Vigenere --
K.Yap Sept 2016
Encrypts the user defined phrase using the vigenere cypher method, using the key that the user defines
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string argv[])
{
//ask for a alphabetical command line input (a key word 'k'), otherwise return an error
    if (argc != 2)
        {
            printf("Usage: %s <key>\n", argv[0]);
            return 1;
        }
   string k = argv[1];
   
    for (int x = 0, y = strlen(k); x < y; x++)
    {
        if (!isalpha(k[x]))
            {
                printf("Usage: %s <key> must be alphabetical\n", argv[0]);
                return 1;
            }
    }
    
//ask for a string P that will be encrypted
    printf("plaintext: ");
    string p = get_string();
    if (p == NULL)
    {
        return 1;
    }

//encrypt each letter in P using each letter in k
  printf("ciphertext: ");
  int h = 0;
  int i = 0;
  int j = 0;
  int n = strlen(p);
  int m = strlen(k);
  while(i < n)
    {
        if (isalpha (p[i]))
        {
            if isupper (p[i])
            {
                printf("%c", ((p[i] - 65 + (toupper(k[j])-65))%26 + 65));
            }
            
            else if islower (p[i])
            {
                printf("%c", ((p[i] - 97 + (tolower(k[j])-97))%26 + 97));
            }
            
            h++;
        }
        else if isprint (p[i])
        {
           printf("%c", p[i]);
        }
        
        i++;
        j = h % m; //TIP: use modulo to wrap back around
    }
    printf("\n");
    return 0;

}
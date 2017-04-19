/*
-- Caesar --
K.Yap Sept 2016
Encrypts the user defined phrase using the caesar cypher method, using the key that the user defines
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }
    // TIP: no need 'else' after the IF statement
    int k = atoi(argv[1]);
    
    printf("plaintext:  ");
    string p = get_string();
    if (p == NULL)
    {
        return 1;
    }
    
    printf("ciphertext: ");
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if isalpha (p[i])
        {
            if isupper (p[i])
            {
                printf("%c", ((p[i] - 65 + k) %26) + 65);
        //convert char no. 65 to 90 to alphabetical index by - and then + 65
            }
            
            else if islower (p[i])
            {
                printf("%c", ((p[i] -97 + k) %26) + 97);
        //97 to 122
            }
        }
        else if isprint (p[i])
        {
           printf("%c", p[i]); 
        }
    }
    printf("\n");
    
    return 0;
    
    
    
}
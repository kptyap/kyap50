#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    string k = argv[1];

    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if(!isalpha(k[i]))
        {
            printf("not alpha");
        }
        else
        {
            printf("alpha");
        }
    }
    
}
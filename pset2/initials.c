/*
-- Initials --
K.Yap Sept 2016
Lists the initials of the name that a user inputs
*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    printf("What is your name?\n");
    string name = GetString();
    if (name != NULL)
    {
        printf("%c", toupper(name[0]));
        for (int i = 0, n = strlen(name); i < n; i++) // TIP: optimise by declaring strlen once not every loop
        {
            if(name[i]==' ') //check to see if equals space, note ' '
                {
                printf("%c", toupper(name[i+1])); 
                }
        }
        printf("\n");
    }
    
}
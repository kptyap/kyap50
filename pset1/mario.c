/*
-- Mario --
K.Yap August 2016
Creates a half pyramid of hashes with the height based off a user's input
*/

#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int height; //declare the variable before the do loop
    do // use a do loop as the check that user input is in the specified range
    {
        printf("Height: ");  //ask for user input
        height = get_int();
    }
    while (height <0 || height >23); //check to make sure input is within 0-23 otherwise ask height again
    
    for (int i = 0; i < height; i++)    
        {
            for (int j = (height-i-1); j > 0; j--) //print this number of spaces
            {
                printf(" ");
            }
            for (int k = (i+2); k > 0; k--) //print this number of hashes
            {
                printf("#");
            }
            printf("\n"); //go to the next line and then repeat the above two loops
        }
    
    }
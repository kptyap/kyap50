/*
-- Greedy --
K.Yap August 2016
Finds the least number of coins 'greedy algorithm' that can be given for a user defined amount of money
*/

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float amnt;
    do
    {
        printf("How much $$ are you owed?");
        amnt = GetFloat();
    }
    while (amnt < 0);
    
    int iamnt = round(amnt*100);
    int count = 0;
    int q = 25;
    int d = 10;
    int n = 5;
    int p = 1;
    
    //printf("The amount before loop is %i\n", iamnt);
    
        while (iamnt - q >= 0)
        {
            iamnt-=q;
            ++count;
        }
        while (iamnt - d >= 0)
        {
            iamnt-=d;
            ++count;
        }        
        while (iamnt - n >= 0)
        {
            iamnt-=n;
            ++count;
        }        
        while (iamnt - p >= 0)
        {
            iamnt-=p;
            ++count;
        }

    //printf("The amount is %i\n", iamnt);
    printf("%i\n", count);
 
}

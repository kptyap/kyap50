#include <cs50.h>
#include <stdio.h>
#include <math.h>


void main(int values[], int n)
{
    int swapcounter = 0;
    do
    {
        swapcounter = 0;
        for (int i = 0; i < n; i++)
        {
            if(values[i] < values[i-1])
            {
                double tempsml = values[i];
                values[i] = values[i-1];
                values[i-1] = tempsml; //swap the larger value with the smaller value
                printf("values i is %d, values i-1 is %d",values[i], values[i-1]);
                swapcounter++;
            }
        }

    }
    while (swapcounter > 0); 
        
    return;
}
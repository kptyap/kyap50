/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int s) //**Binary Search by Kyap**
{
    int low = 0;
    int high = s;
    int mid = round((low + high) / 2); //Note the midpoint formula
    
    while (high >= low) //while you have not found the value
    {   
        mid = round((low + high) / 2);
        
        if (value < values[mid]) //if value is smaller than midpoint
        {
            high = mid - 1; //look in the left half and adjust max boundary
        }  
        
        else if (value > values[mid])  //if value is larger than midpoint
        {
            low = mid + 1; //look in the right half and adjust min boundary
        }
        else
            return true; //else that means midpoint must be what we are looking for
    }
        return false;
}

/**
 * Sorts array of n values.
 */

void sort(int values[], int n)
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
                swapcounter++;
            }
        }

    }
    while (swapcounter > 0); 
    
    for (int i = 0; i < n; i++)
        printf("%d\n",values[i]);
        
    return;
}
/**
linear search

 * bool search(int value, int values[], int n)
{
    if (n < 1)
        return false;
    else
        for (int i = 0; i < n; i++)
        {
            if (value == values[i])
                return true;
            if (i == n)
                return false;
        }
        return false;       //!! Needed for the case where n is negative and thus i is not less than n, and so the for loop never runs, and control moves to whatever comes after the for loop, but if there is nothing after the for loop then it can't return a boolean value.
}
*/
//test

#include <stdio.h>
#include <cs50.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

int main(void)
{
   int winboard[DIM_MAX][DIM_MAX];
   int d = GetInt();
 //  winboard[0][0] = 1;
   
   for (int y = 0; y < d; y++) 
   {    
      for (int x = 0; x < d; x++)
      {
         winboard[y][x] = (x+1)+(y*d);
         printf("%2d", winboard[y][x]);
      }
   }
}
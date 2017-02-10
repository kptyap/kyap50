/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int main(void)
{
    // open input file, declare a FILE type pointer 'inptr', pointee is opened file
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open card.raw\n");
        return 1;
    }
    
    //open outfile indicator, declare FILE type pointer 'outptr' (best to open it outside the loop)
    FILE* outptr;
    
    //create temporary storage - a 'buffer' of exactly 512 bytes
    unsigned char buf[512];
    
    //create counters
    int foundjpg = 0;
    
    //iterate through bytes in inptr
    //read every block of 512 bytes looking for start of .jpg
    while (fread(buf, 512, 1, inptr))
    {
    //if the first four bytes of the read buffer file match those of a jpg
        if(buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] <= 239 && buf[3] >= 224))
        {
            char title[32];
            //if we are starting a jpg other than the first, close the prior file
            if (foundjpg > 0)
                fclose(outptr);
         
            //create a 00x.jpg filename in directory
            sprintf(title, "%03d.jpg", foundjpg);
            
            //open that 00x.jpg, set as pointee to the pointer 'outptr'
            outptr = fopen(title, "a");
            
            foundjpg ++;
        }
    //write that block of 512 bytes to the 00x.jpg, if we have already found the first jpg
        if (foundjpg > 0) 
            fwrite(buf, 512, 1, outptr);
    }
    if (foundjpg < 1)
    {
        fprintf(outptr, "No jpgs on file\n");
        return 1;
    }
    
    //reached the end of inptr, time to close up and finish
    fclose(inptr);
    fclose(outptr);
    return 0;

}

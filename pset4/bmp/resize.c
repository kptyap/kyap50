/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * resizes a BMP. Based on cs50 copy.c
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"


int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames and size
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    /**save values of current header
    LONG oldHeight = bi.biHeight;
    LONG oldWidth = bi.biWidth;
    */

    //establish new headers from infile headers
    BITMAPFILEHEADER bf2 = bf;
    BITMAPINFOHEADER bi2 = bi;
    
    //edit new infile header's width and height
    bi2.biHeight = bi.biHeight * n;
    bi2.biWidth = bi.biWidth * n;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding2 = (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //edit new infile header's size based off padding
    bi2.biSizeImage = (bi2.biWidth * 3 + padding2) * abs(bi2.biHeight);
    bf2.bfSize = bi2.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines (vertically)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int m = 0; m < n; m++) //loop to scale vertically
        {
            // iterate over pixels in infile's scanline (horizontally)
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write each horizontal RGB triple pixel to outfile n times
                for (int k = 0; k < n; k++)
                {    
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding in the infile, if any
            fseek(inptr, padding, SEEK_CUR);
    
            // write padding into outfile using fputc
            for (int l = 0; l < padding2; l++)
            {
                fputc(0x00, outptr);
            }
            if (m < n-1) //cheated
            {
                // seek back to the beginning of the same row in the infile to scale vertically
                fseek(inptr, -(long int)(bi.biWidth * sizeof(RGBTRIPLE) + padding) , SEEK_CUR);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

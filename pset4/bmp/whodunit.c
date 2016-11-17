/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: whodunit\n");
        return 1;
    }

    // open input file 
    FILE* cluePtr = fopen(argv[1], "r"); //use commandline argument 1 as the input file
    if (cluePtr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // open output file
    FILE* solPtr = fopen("solution.bmp", "w");
    if (solPtr == NULL)
    {
        fclose(cluePtr);
        fprintf(stderr, "Could not create %s.\n", "solution.bmp");
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, cluePtr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, cluePtr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(solPtr);
        fclose(cluePtr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, solPtr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, solPtr);

   // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, cluePtr);

            // write RGB triple to outfile
            if(triple.rgbtRed == 255)
            {
		triple.rgbtRed = 0;
  		triple.rgbtBlue = 100;
		triple.rgbtGreen = 60;
            } 
            fwrite(&triple, sizeof(RGBTRIPLE), 1, solPtr);
	    
	    
        }

        // skip over padding, if any
        fseek(cluePtr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
            fputc(0x00, solPtr);
    }

    // close infile
    fclose(cluePtr);

    // close outfile
    fclose(solPtr);

    // that's all folks
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        return 1;
    }

    // remember filenames
    char* inFile = argv[2];
    char* outFile = argv[3];
    int factor = atoi(argv[1]);
    
    if (factor < 1 || factor > 100)
    {
        printf("Factor needs to be within range 1-100!\n");
        return 1;
    }

    // open input file 
    FILE* inPtr = fopen(inFile, "r");
    if (inPtr == NULL) //check for null pointer
    {
        printf("Couldn't open %s.\n", inFile);
        return 2;
    }

    // open output file
    FILE* outPtr = fopen(outFile, "w");
    if (outPtr == NULL) //check for null pointer
    {
        fclose(inPtr);
        fprintf(stderr, "Could not create %s.\n", outFile);
        return 3;
    }

    // read BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_r;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inPtr);
    bf_r = bf;
    BITMAPINFOHEADER bi, bi_r;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inPtr);
    bi_r = bi;

    // check if the input file is a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outPtr);
        fclose(inPtr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Get new dimensions
    bi_r.biWidth  = bi.biWidth * factor; //multiplying by the user input factor
    bi_r.biHeight = bi.biHeight * factor;
    
    // Determine the old and new paddings
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    int res_padding = (4 - (bi_r.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    
    // Determine new image sizes
    bi_r.biSizeImage = (bi_r.biWidth * sizeof(RGBTRIPLE) + res_padding) * abs(bi_r.biHeight);
    bf_r.bfSize = bf.bfSize - bi.biSizeImage + bi_r.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_r, sizeof(BITMAPFILEHEADER), 1, outPtr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_r, sizeof(BITMAPINFOHEADER), 1, outPtr);

    // scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < factor; j++)
        {  
            // pixels
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temp
                RGBTRIPLE triple;

                // RGB triple
                fread(&triple, sizeof(RGBTRIPLE), 1, inPtr);

                // generate the output file by using the factor
                for (int l = 0; l < factor; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outPtr);    
            }
            
            // Add a new padding
            for (int l = 0; l < res_padding; l++)
                fputc(0x00, outPtr);
            
            if (j < factor - 1)
                fseek(inPtr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }

        // Skip over padding, if any
        fseek(inPtr, padding, SEEK_CUR);
    }

    // close files
    fclose(inPtr);
    fclose(outPtr);

    // that's all folks
    return 0;
}

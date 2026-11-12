#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

void bmpColorrw()
{
    FILE* infile;

    if ((infile = fopen("ImgColor.bmp", "rb")) == NULL) {
        printf("No Image File");
        return;
    }

    // BMP Header Information
    BITMAPFILEHEADER hf;
    BITMAPINFOHEADER hInfo;
    fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);//14 bytes
    fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);//40 bytes
    //RGBQUAD hRGB[256];
    //fread(hRGB, sizeof(RGBQUAD), 256, infile);//read color pallete

    // Memory
    BYTE* lpImg = (BYTE*)malloc(hInfo.biWidth * hInfo.biHeight * 3);
    int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
    BYTE padding[4] = { 0, };
    for (int i = 0; i < hInfo.biHeight; i++) {
        BYTE* row = lpImg + i * hInfo.biWidth * 3;
        fread(row, sizeof(BYTE), hInfo.biWidth * 3, infile);
        fread(padding, sizeof(BYTE), WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth) - hInfo.biWidth*3, infile);
    }
    fclose(infile);

    // Image Output
    FILE* outfile = fopen("ImgColor.ppm", "wb");
    fprintf(outfile, "P6\n");//magic no.
    fprintf(outfile, "%d %d\n", hInfo.biWidth, hInfo.biHeight);
    fprintf(outfile, "255\n");//max. value
    fwrite(lpImg, sizeof(char), hInfo.biWidth * hInfo.biHeight * 3, outfile);
    fclose(outfile);

    //delete[] lpImg;//for c++
    free(lpImg);
}

void main()
{
    bmpColorrw();
}
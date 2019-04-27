// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize f infile outfile\n");
        return 1;
    }
    // перевіряємо чи масштаб типу float or integer
    int sc_f = 0;
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            sc_f++;
        }
        if (!isdigit(argv[1][i]) && argv[1][i] != '.')
        {
            sc_f += 2;
        }
    }
    if (sc_f > 1)
    {
        printf("n, the resize factor, must be an integer or float.\n");
        return 2;
    }
    // перетворюємо рядок в числове значення типу float
    float scale = 0;
    scale = atof(argv[1]);
    // перевіряємо чи масштаб в межах допуску
    if (scale <= 0 || scale > 100)
    {
        printf("The resize factor, must satisfy 0 < n <= 100.\n");
        return 3;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
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
        printf("Unsupported file format.\n");
        return 6;
    }
    // зберігаємо ширину та висоту - в пікселях
    long width = bi.biWidth;
    long height = bi.biHeight;
    // висота по модулю
    long hei = bi.biHeight;
    if (bi.biHeight < 0)
    {
        hei = height * (-1);
    }
    // заокруглюємо коефіцієнт масштабування до десятих
    scale = roundf(scale * 10) / 10;
    // коли зменшуєм зoбраження і ширина рядка = початковій ширині зображення
    if (ceil(width * scale) == width && scale < 1)
    {
        scale = scale - 0.1;
    }
    // коли збільшуємо і остача від ділення нової ширини на ширину початкового зображення =0
    if ((int)ceil(width * scale) % width == 0)
    {
        scale = ceil(scale);
    }
    // height  -pixel
    if (height > 0)
    {
        bi.biHeight = ceil(height * scale);
    }
    else
    {
        bi.biHeight = ceil(hei * scale) * (-1);
    }
    // нова висота по модулю
    long hei_new = bi.biHeight;
    if (bi.biHeight < 0)
    {
        hei_new = bi.biHeight * (-1);
    }
    // width  -pixel
    bi.biWidth = ceil(width * scale);
    // determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    // new padding
    int padding_new = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // new sizeimage and bfsize
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding_new) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    /***************************************************************
                        збільшуємо файл
    ***************************************************************/
    if (scale >= 1)
    {
        //кількість пікселів або рядків, що необхідно записати підряд
        int scale_wh = scale;
        // кількість додаткових пікселів по ширині за мінусом цілих
        int w_write_add = bi.biWidth % width;
        // j -ий символ після якого вставляємо додатковий 1 піксель по ширині
        int w_write = 0;
        int w_write_w = w_write;
        int w_write_1 = 0;
        if (w_write_add == 0)
        {
            w_write = -1;
        }
        else
        {
            w_write = floor((double)width / (double)w_write_add) - 1;
            w_write_1 = floor((double)width / (double)w_write_add);
        }
        // кількість додаткових рядків за мінусом цілих
        int h_write_add = bi.biWidth % width;
        // i -ий символ після якого вставляємо додатковий рядок
        int h_write = 0;
        int h_write_h = w_write;
        int h_write_1 = 0;
        if (h_write_add == 0)
        {
            h_write = -1;
        }
        else
        {
            h_write = floor((double)hei / (double)h_write_add) - 1;
            h_write_1 = floor((double)hei / (double)h_write_add);
        }
        // лічильник цілих рядків записаних підряд
        int h = 0;
        // лічильник всіх рядків
        int h_all = 0;
        // лічильник всіх пікселів в рядку
        int w_wr = 0;


        // iterate over infile's scanlines
        for (int i = 0; i < hei_new; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < width; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int p = 0; p < scale_wh; p++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    w_wr++;
                }
                if (w_write == j && w_write_add != 0 && w_wr != bi.biWidth)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    w_wr++;
                    w_write = w_write + w_write_1;
                }
            }
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding_new; k++)
            {
                fputc(0x00, outptr);
            }
            w_wr = 0;
            // присвоюємо w_wr початкового значення  а х = 0
            w_write = w_write_w;
            h_all++;
            h++;
            // return to the beginning of the line for re-reading
            if (h < scale_wh)
            {
                fseek(inptr, (width * sizeof(RGBTRIPLE)) * (-1), SEEK_CUR);
            }
            else if (h == scale_wh && h_write_add != 0 && h_all != hei_new)
            {
                // skip over padding, if any
                fseek(inptr, (width * sizeof(RGBTRIPLE)) * (-1), SEEK_CUR);
            }
            else
            {
                fseek(inptr, padding, SEEK_CUR);
                h = 0;
            }
        }
    }
    /***************************************************************
                        зменшуємо файл
    ***************************************************************/
    else
    {
        // необхідна кількість пропущених пікселів по ширині
        int skip = width - bi.biWidth;
        skip = abs(skip);
        // необхідна кількість пропущених рядків по висоті
        int h_skip = hei - hei_new;
        h_skip = abs(h_skip);
        // кількість пікселів w і рядків h, що необхідно пропустити підряд
        int w_skip_1 = ceil((double)skip / (double)bi.biWidth);
        int h_skip_1 = ceil((double)h_skip / (double)hei_new);
        // кількість обов'язкових пікселів чи рядків, які необхідно записати підряд
        int w_write = ceil((double)bi.biWidth / (double)skip);
        int h_write = ceil((double)hei_new / (double)h_skip);

        // лічильник записаних рядків h_wr та пропущених рядків h_s по висоті
        int h_wr = 0;
        int h_s = 0;
        // iterate over infile's scanlines
        for (int i = 0; i < hei; i++)
        {
            if (h_wr < h_write)
            {
                // лічильник записаних пікселів w_wr та пропущених пікселів w_s по ширині
                int w_wr = 0;
                int w_s = 0;
                // iterate over pixels in scanline
                for (int j = 0; j < width; j++)
                {
                    if (w_wr < w_write)
                    {
                        // temporary storage
                        RGBTRIPLE triple;
                        // read RGB triple from infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                        w_wr++;
                    }
                    else
                    {
                        // пропускаємо пікселі, які не потрібно записувати
                        fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                        w_s++;
                        if (w_s == w_skip_1)
                        {
                            // обнуляємо лічильник записаних пікселів
                            w_wr = 0;
                            w_s = 0;
                        }
                    }
                }

                // вставляємо пусті пікселі за необхідністю у outptr
                for (int k = 0; k < padding_new; k++)
                {
                    fputc(0x00, outptr);
                }
                // пропускаємо пусті пікселі вихідного файлу inptr
                fseek(inptr, padding, SEEK_CUR);

                h_wr++;
            }
            else
            {
                // пропускаємо рядки, які не потрібно зчитувати
                fseek(inptr, width * sizeof(RGBTRIPLE) + padding, SEEK_CUR);
                h_s++;
                if (h_s == h_skip_1)
                {
                    h_wr = 0;
                    h_s = 0;
                }
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

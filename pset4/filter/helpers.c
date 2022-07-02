#include "helpers.h"
#include <math.h>
#include <stdio.h>

//------SEPIA FUNCTIONS------
int sepiaBlue(float value_blue, float value_green, float value_red);
int sepiaGreen(float value_blue, float value_green, float value_red);
int sepiaRed(float value_blue, float value_green, float value_red);
//---------------------------

void swap(BYTE *a, BYTE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float oBlue; // original Blue
    float oGreen; // original Green
    float oRed; // originalRed


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oBlue = (float)image[i][j].rgbtBlue;
            oGreen = (float)image[i][j].rgbtGreen;
            oRed = (float)image[i][j].rgbtRed;


            image[i][j].rgbtBlue = sepiaBlue(oBlue, oGreen, oRed);
            image[i][j].rgbtGreen = sepiaGreen(oBlue, oGreen, oRed);
            image[i][j].rgbtRed = sepiaRed(oBlue, oGreen, oRed);
        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfwidth = (width / 2);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfwidth; j++)
        {
            int dif = (width - 1) - j;
            swap(&image[i][j].rgbtBlue, &image[i][dif].rgbtBlue);
            swap(&image[i][j].rgbtGreen, &image[i][dif].rgbtGreen);
            swap(&image[i][j].rgbtRed, &image[i][dif].rgbtRed);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float oBlue[height][width]; // original Blue
    float oGreen[height][width]; // original Green
    float oRed[height][width]; // original Red


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oBlue[i][j] = (float)image[i][j].rgbtBlue;
            oGreen[i][j] = (float)image[i][j].rgbtGreen;
            oRed[i][j] = (float)image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height + 1; i++)
    {
        for (int j = 0; j < width + 1; j++)
        {
            if (i == 0 && j == 0)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i + 1][j] + oBlue[i][j + 1] + oBlue[i + 1][j + 1]) / 4);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i + 1][j] + oRed[i][j + 1] + oRed[i + 1][j + 1]) / 4);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i + 1][j] + oGreen[i][j + 1] + oGreen[i + 1][j + 1]) / 4);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else if (i == height - 1 && j == width - 1)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i - 1][j] + oBlue[i][j - 1] + oBlue[i - 1][j - 1]) / 4);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i - 1][j] + oRed[i][j - 1] + oRed[i - 1][j - 1]) / 4);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i - 1][j] + oGreen[i][j - 1] + oGreen[i - 1][j - 1]) / 4);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else if (i == 0 && j == width - 1)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i + 1][j] + oBlue[i][j - 1] + oBlue[i + 1][j - 1]) / 4);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i + 1][j] + oRed[i][j - 1] + oRed[i + 1][j - 1]) / 4);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i + 1][j] + oGreen[i][j - 1] + oGreen[i + 1][j - 1]) / 4);
                image[i][j].rgbtGreen = aGreen;
                goto next;

            }

            else if (i == height - 1 && j == 0)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i - 1][j] + oBlue[i][j + 1] + oBlue[i - 1][j + 1]) / 4);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i - 1][j] + oRed[i][j + 1] + oRed[i - 1][j + 1]) / 4);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i - 1][j] + oGreen[i][j + 1] + oGreen[i - 1][j + 1]) / 4);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else if (i == 0 && j != width - 1)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i + 1][j] + oBlue[i][j + 1] + oBlue[i][j - 1] + oBlue[i + 1][j - 1] + oBlue[i + 1][j + 1]) /
                                  6);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i + 1][j] + oRed[i][j + 1] + oRed[i][j - 1] + oRed[i + 1][j - 1] + oRed[i + 1][j + 1]) / 6);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i + 1][j] + oGreen[i][j + 1] + oGreen[i][j - 1] + oGreen[i + 1][j - 1] + oGreen[i + 1][j +
                                    1]) / 6);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else if (j == 0 && i != height - 1)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i + 1][j] + oBlue[i][j + 1] + oBlue[i - 1][j] + oBlue[i - 1][j + 1] + oBlue[i + 1][j + 1]) /
                                  6);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i + 1][j] + oRed[i][j + 1] + oRed[i - 1][j] + oRed[i - 1][j + 1] + oRed[i + 1][j + 1]) / 6);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i + 1][j] + oGreen[i][j + 1] + oGreen[i - 1][j] + oGreen[i - 1][j + 1] + oGreen[i + 1][j +
                                    1]) / 6);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else if (j == width - 1 && i != 0)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i + 1][j] + oBlue[i - 1][j] + oBlue[i][j - 1] + oBlue[i - 1][j - 1] + oBlue[i + 1][j - 1]) /
                                  6);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i + 1][j] + oRed[i - 1][j] + oRed[i][j - 1] + oRed[i - 1][j - 1] + oRed[i + 1][j - 1]) / 6);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i + 1][j] + oGreen[i - 1][j] + oGreen[i][j - 1] + oGreen[i - 1][j - 1] + oGreen[i + 1][j -
                                    1]) / 6);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else if (i == height - 1 && j != 0)
            {
                int aBlue = round((oBlue[i][j] + oBlue[i - 1][j] + oBlue[i][j + 1] + oBlue[i][j - 1] + oBlue[i - 1][j - 1] + oBlue[i - 1][j + 1]) /
                                  6);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i - 1][j] + oRed[i][j + 1] + oRed[i][j - 1] + oRed[i - 1][j - 1] + oRed[i - 1][j + 1]) / 6);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i - 1][j] + oGreen[i][j + 1] + oGreen[i][j - 1] + oGreen[i - 1][j - 1] + oGreen[i - 1][j +
                                    1]) / 6);
                image[i][j].rgbtGreen = aGreen;
                goto next;
            }

            else
            {
                int aBlue = round((oBlue[i][j] + oBlue[i + 1][j] + oBlue[i][j + 1] + oBlue[i][j - 1]
                                   + oBlue[i - 1][j] + oBlue[i - 1][j - 1] + oBlue[i - 1][j + 1] + oBlue[i + 1][j - 1] + oBlue[i + 1][j + 1]) / 9);
                image[i][j].rgbtBlue = aBlue;

                int aRed = round((oRed[i][j] + oRed[i + 1][j] + oRed[i][j + 1] + oRed[i][j - 1]
                                  + oRed[i - 1][j] + oRed[i - 1][j - 1] + oRed[i - 1][j + 1] + oRed[i + 1][j - 1] + oRed[i + 1][j + 1]) / 9);
                image[i][j].rgbtRed = aRed;

                int aGreen = round((oGreen[i][j] + oGreen[i + 1][j] + oGreen[i][j + 1]
                                    + oGreen[i][j - 1] + oGreen[i - 1][j] + oGreen[i - 1][j - 1] + oGreen[i - 1][j + 1] + oGreen[i + 1][j - 1] + oGreen[i + 1][j + 1]) /
                                   9);
                image[i][j].rgbtGreen = aGreen;
                goto next;

next:
                continue;
            }

        }
    }

    return;
}

// sepias the shit out of those Blue pixels
int sepiaBlue(float value_blue, float value_green, float value_red)
{
    float red = .272 * value_red;
    float green = .534 * value_green;
    float blue = .131 * value_blue;

    int result;


    result = round(red + green + blue);

    if (result > 255)
    {
        return 255;
    }
    else
    {
        return result;
    }

}

// sepias the shit out of those Green pixels
int sepiaGreen(float value_blue, float value_green, float value_red)
{
    float red = .349 * value_red; // Calculates the value of red after sepia
    float green = .686 * value_green; // Calculates the value of green after sepia
    float blue = .168 * value_blue; // Calculates the value of blue after sepia

    int result;



    result = round(red + green + blue);

    if (result > 255)
    {
        return 255;
    }
    else
    {
        return result;
    }

}
// sepias the shit out of those Red pixels
int sepiaRed(float value_blue, float value_green, float value_red)
{



    float red = .393 * value_red; // Calculates the value of red after sepia
    float green = .769 * value_green; // Calculates the value of green after sepia
    float blue = .189 * value_blue; // Calculates the value of blue after sepia

    int result;



    result = round(red + green + blue);

    if (result > 255)
    {
        return 255;
    }
    else
    {
        return result;
    }
}

void swap(BYTE *a, BYTE *b)
{
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
}












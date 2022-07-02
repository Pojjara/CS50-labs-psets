#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int oBlue[height][width]; // original Blue
    int oGreen[height][width]; // original Green
    int oRed[height][width]; // original Red


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            oBlue[i][j] = image[i][j].rgbtBlue;
            oGreen[i][j] = image[i][j].rgbtGreen;
            oRed[i][j] = image[i][j].rgbtRed;
        }
    }




    for (int i = 0; i < height + 1; i++)
    {
        for (int j = 0; j < width + 1; j++)
        {
            if (i == 0 && j == 0)
            {
                int GxBlue = oBlue[i][j + 1] * 2 + oBlue[i + 1][j + 1] * 1;
                int GyBlue =  oBlue[i + 1][j] * 2 + oBlue[i + 1][j + 1] * 1;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i][j + 1] * 2 + oRed[i + 1][j + 1] * 1;
                int GyRed =  oRed[i + 1][j] * 2 + oRed[i + 1][j + 1] * 1;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i][j + 1] * 2 + oGreen[i + 1][j + 1] * 1;
                int GyGreen =  oGreen[i + 1][j] * 2 + oGreen[i + 1][j + 1] * 1;

                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;
                goto next;
            }

            else if (i == height - 1 && j == width - 1)
            {
                int GxBlue = oBlue[i - 1][j - 1] * -1 + oBlue[i][j - 1] * -2;
                int GyBlue =  oBlue[i - 1][j - 1] * -1 + oBlue[i - 1][j] * -2;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));

                int GxRed = oRed[i - 1][j - 1] * -1 + oRed[i][j - 1] * -2;
                int GyRed =  oRed[i - 1][j - 1] * -1 + oRed[i - 1][j] * -2;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i - 1][j - 1] * -1 + oGreen[i][j - 1] * -2;
                int GyGreen =  oGreen[i - 1][j - 1] * -1 + oGreen[i - 1][j] * -2;

                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;
                goto next;
            }

            else if (i == 0 && j == width - 1)
            {
                int GxBlue = oBlue[i + 1][j - 1] * -1 + oBlue[i][j - 1] * -2;
                int GyBlue =  oBlue[i + 1][j - 1] * 1 + oBlue[i + 1][j] * 2;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i + 1][j - 1] * -1 + oRed[i][j - 1] * -2;
                int GyRed =  oRed[i + 1][j - 1] * 1 + oRed[i + 1][j] * 2;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i + 1][j - 1] * -1 + oGreen[i][j - 1] * -2;
                int GyGreen =  oGreen[i + 1][j - 1] * 1 + oGreen[i + 1][j] * 2;

                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;

                goto next;

            }

            else if (i == height - 1 && j == 0)
            {
                int GxBlue = oBlue[i - 1][j + 1] * 1 + oBlue[i][j + 1] * 2;
                int GyBlue =  oBlue[i - 1][j] * -2 + oBlue[i - 1][j + 1] * -1;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i - 1][j + 1] * 1 + oRed[i][j + 1] * 2;
                int GyRed =  oRed[i - 1][j] * -2 + oRed[i - 1][j + 1] * -1;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i - 1][j + 1] * 1 + oGreen[i][j + 1] * 2;
                int GyGreen =  oGreen[i - 1][j] * -2 + oGreen[i - 1][j + 1] * -1;

                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;

                goto next;
            }

            else if (i == 0 && j != width - 1)
            {
                int GxBlue = oBlue[i][j - 1] * -2 + oBlue[i][j + 1] * 2 + oBlue[i + 1][j - 1] * -1 + oBlue[i + 1][j + 1] * 1;
                int GyBlue =  oBlue[i + 1][j - 1] * 1 + oBlue[i + 1][j] * 2 + oBlue[i + 1][j + 1] * 1;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i][j - 1] * -2 + oRed[i][j + 1] * 2 + oRed[i + 1][j - 1] * -1 + oRed[i + 1][j + 1] * 1;
                int GyRed =  oRed[i + 1][j - 1] * 1 + oRed[i + 1][j] * 2 + oRed[i + 1][j + 1] * 1;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i][j - 1] * -2 + oGreen[i][j + 1] * 2 + oGreen[i + 1][j - 1] * -1 + oGreen[i + 1][j + 1] * 1;
                int GyGreen =  oGreen[i + 1][j - 1] * 1 + oGreen[i + 1][j] * 2 + oGreen[i + 1][j + 1] * 1;

                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;
                goto next;
            }

            else if (j == 0 && i != height - 1)
            {
                int GxBlue = oBlue[i - 1][j + 1] * 1 + oBlue[i][j + 1] * 2 + oBlue[i + 1][j + 1] * 1;
                int GyBlue =  oBlue[i - 1][j] * -2 + oBlue[i - 1][j + 1] * -1 + oBlue[i + 1][j + 1] * 1 + oBlue[i + 1][j] * 2;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i - 1][j + 1] * 1 + oRed[i][j + 1] * 2 + oRed[i + 1][j + 1] * 1;
                int GyRed =  oRed[i - 1][j] * -2 + oRed[i - 1][j + 1] * -1 + oRed[i + 1][j + 1] * 1 + oRed[i + 1][j] * 2;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i - 1][j + 1] * 1 + oGreen[i][j + 1] * 2 + oGreen[i + 1][j + 1] * 1;
                int GyGreen =  oGreen[i - 1][j] * -2 + oGreen[i - 1][j + 1] * -1 + oGreen[i + 1][j + 1] * 1 + oGreen[i + 1][j] * 2;



                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;
                goto next;
            }

            else if (j == width - 1 && i != 0)
            {
                int GxBlue = oBlue[i - 1][j - 1] * -1 + oBlue[i][j - 1] * -2 + oBlue[i + 1][j - 1] * -1;
                int GyBlue =  oBlue[i - 1][j] * -2 + oBlue[i - 1][j - 1] * -1 + oBlue[i + 1][j - 1] * 1 + oBlue[i + 1][j] * 2;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i - 1][j - 1] * -1 + oRed[i][j - 1] * -2 + oRed[i + 1][j - 1] * -1;
                int GyRed =  oRed[i - 1][j] * -2 + oRed[i - 1][j - 1] * -1 + oRed[i + 1][j - 1] * 1 + oRed[i + 1][j] * 2;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i - 1][j - 1] * -1 + oGreen[i][j - 1] * -2 + oGreen[i + 1][j - 1] * -1;
                int GyGreen =  oGreen[i - 1][j] * -2 + oGreen[i - 1][j - 1] * -1 + oGreen[i + 1][j - 1] * 1 + oGreen[i + 1][j] * 2;



                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;
                goto next;
            }

            else if (i == height - 1 && j != 0)
            {
                int GxBlue = oBlue[i - 1][j - 1] * -1 + oBlue[i][j - 1] * -2 + oBlue[i - 1][j + 1] * 1 + oBlue[i][j + 1] * 2;
                int GyBlue =  oBlue[i - 1][j] * -2 + oBlue[i - 1][j - 1] * -1 + oBlue[i - 1][j + 1] * -1;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i - 1][j - 1] * -1 + oRed[i][j - 1] * -2 + oRed[i - 1][j + 1] * 1 + oRed[i][j + 1] * 2;
                int GyRed =  oRed[i - 1][j] * -2 + oRed[i - 1][j - 1] * -1 + oRed[i - 1][j + 1] * -1;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));



                int GxGreen = oGreen[i - 1][j - 1] * -1 + oGreen[i][j - 1] * -2 + oGreen[i - 1][j + 1] * 1 + oGreen[i][j + 1] * 2;
                int GyGreen =  oGreen[i - 1][j] * -2 + oGreen[i - 1][j - 1] * -1 + oGreen[i - 1][j + 1] * -1;



                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;
                goto next;
            }

            else
            {
                int GxBlue = oBlue[i - 1][j - 1] * -1 + oBlue[i][j - 1] * -2 + oBlue[i + 1][j - 1] * -1 + oBlue[i - 1][j + 1] * 1 + oBlue[i][j + 1]
                             * 2 + oBlue[i + 1][j + 1] * 1;
                int GyBlue =  oBlue[i - 1][j - 1] * -1 + oBlue[i - 1][j] * -2 + oBlue[i + 1][j - 1] * 1 + oBlue[i - 1][j + 1] * -1 + oBlue[i + 1][j]
                              * 2 + oBlue[i + 1][j + 1] * 1;

                int resultBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));


                int GxRed = oRed[i - 1][j - 1] * -1 + oRed[i][j - 1] * -2 + oRed[i + 1][j - 1] * -1 + oRed[i - 1][j + 1] * 1 + oRed[i][j + 1] * 2 +
                            oRed[i + 1][j + 1] * 1;
                int GyRed = oRed[i - 1][j - 1] * -1 + oRed[i - 1][j] * -2 + oRed[i + 1][j - 1] * 1 + oRed[i - 1][j + 1] * -1 + oRed[i + 1][j] * 2 +
                            oRed[i + 1][j + 1] * 1;

                int resultRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));


                int GxGreen = oGreen[i - 1][j - 1] * -1 + oGreen[i][j - 1] * -2 + oGreen[i + 1][j - 1] * -1 + oGreen[i - 1][j + 1] * 1 + oGreen[i][j
                              + 1] * 2 + oGreen[i + 1][j + 1] * 1;
                int GyGreen = oGreen[i - 1][j - 1] * -1 + oGreen[i - 1][j] * -2 + oGreen[i + 1][j - 1] * 1 + oGreen[i - 1][j + 1] * -1 + oGreen[i +
                              1][j] * 2 + oGreen[i + 1][j + 1] * 1;

                int resultGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                if (resultBlue > 255)
                {
                    resultBlue = 255;
                }
                if (resultRed > 255)
                {
                    resultRed = 255;
                }
                if (resultGreen > 255)
                {
                    resultGreen = 255;
                }

                image[i][j].rgbtBlue = resultBlue;
                image[i][j].rgbtRed = resultRed;
                image[i][j].rgbtGreen = resultGreen;

next:
                continue;
            }

        }
    }

    return;
}


void swap(BYTE *a, BYTE *b)
{
    BYTE tmp = *a;
    *a = *b;
    *b = tmp;
}
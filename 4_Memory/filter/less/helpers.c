#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take avarage of red, green and blue
            int sumRGB = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            float avgRGB = round((float) sumRGB / 3);

            // Update pixel volumes
            image[i][j].rgbtRed = avgRGB;
            image[i][j].rgbtGreen = avgRGB;
            image[i][j].rgbtBlue = avgRGB;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Measure sepia for each color at each pixel
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue);

            // Constraint sepia values under RGB limits
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Update original values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE horizontal_axis[width];
    for (int i = 0; i < height; i++)
    {
        // Create a reflection of current line (i)
        for (int j = 0; j < width; j++)
        {
            int last_horizontal_index = width - 1;
            horizontal_axis[last_horizontal_index - j].rgbtRed = image[i][j].rgbtRed;
            horizontal_axis[last_horizontal_index - j].rgbtGreen = image[i][j].rgbtGreen;
            horizontal_axis[last_horizontal_index - j].rgbtBlue = image[i][j].rgbtBlue;
        }
        // Write the reflected line over the original one (i)
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = horizontal_axis[j].rgbtRed;
            image[i][j].rgbtGreen = horizontal_axis[j].rgbtGreen;
            image[i][j].rgbtBlue = horizontal_axis[j].rgbtBlue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blured_img[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    // copy 
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                       image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed) /
                              4);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                              4);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                       image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue) /
                              4);
                }
                else if (j == (width - 1))
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                       image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) /
                              4);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                       image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) /
                              4);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                       image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) /
                              4);
                }
                else
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                       image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                                       image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) /
                              6);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                       image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) /
                              6);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                       image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) /
                              6);
                }
            }
            else if (i == (height - 1))
            {
                if (j == 0)
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                                       image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed) /
                              4);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                       image[i - 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen) /
                              4);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue) /
                              4);
                }
                else if (j == (width - 1))
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                       image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed) /
                              4);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) /
                              4);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) /
                              4);
                }
                else
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i][j - 1].rgbtRed +
                                       image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                       image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed) /
                              6);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                       image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen) /
                              6);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue) /
                              6);
                }
            }
            else
            {
                if (j == 0)
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                                       image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed +
                                       image[i - 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed) /
                              6);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                       image[i - 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen) /
                              6);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                       image[i - 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue) /
                              6);
                }
                else if (j == (width - 1))
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i + 1][j].rgbtRed +
                                       image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed +
                                       image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed) /
                              6);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) /
                              6);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                                       image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                       image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) /
                              6);
                }
                else
                {
                    blured_img[i][j].rgbtRed =
                        round((float) (image[i][j].rgbtRed + image[i + 1][j - 1].rgbtRed +
                                       image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                       image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                       image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                       image[i][j - 1].rgbtRed) /
                              9);
                    blured_img[i][j].rgbtGreen =
                        round((float) (image[i][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                                       image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                       image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                       image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                       image[i][j - 1].rgbtGreen) /
                              9);
                    blured_img[i][j].rgbtBlue =
                        round((float) (image[i][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                                       image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                       image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                       image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                       image[i][j - 1].rgbtBlue) /
                              9);
                }
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blured_img[i][j].rgbtRed;
            image[i][j].rgbtGreen = blured_img[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blured_img[i][j].rgbtBlue;
        }
    }
}

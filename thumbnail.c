// Maame Adwoa Ocran
// Assignment 2- main file

#include <stdio.h>
#include <stdlib.h>
#include "thumbnail.h"

void readImageData(FILE *file, Image *image)
{
  fscanf(file, "P5 %d %d %d\n", &image->width, &image->height, &image->max);
}

void readPixels(FILE *file, Image *image)
{
  int numPixels = image->width * image->height;
  image->pixels = (unsigned char *)malloc(sizeof(unsigned char) * numPixels);
  fread(image->pixels, sizeof(unsigned char), numPixels, file);
}

void writeImageData(FILE *file, int width, int height, int max)
{
  fprintf(file, "P5\n%d %d\n%d\n", width, height, max);
}

void writePixels(FILE *file, unsigned char *pixels, int numPixels)
{
  fwrite(pixels, sizeof(unsigned char), numPixels, file);
}

void generateThumbnail(Image *original, Image *thumbnail)
{
  int originalWidth = original->width;
  int originalHeight = original->height;
  int thumbnailWidth = 300;
  int thumbnailHeight = (originalHeight * thumbnailWidth) / originalWidth;
  int numPixels = thumbnailWidth * thumbnailHeight;
  thumbnail->width = thumbnailWidth;
  thumbnail->height = thumbnailHeight;
  thumbnail->max = original->max;
  thumbnail->pixels = (unsigned char *)malloc(sizeof(unsigned char) * numPixels);

  int widthRatio = (originalWidth << 16) / thumbnailWidth + 1;
  int heightRatio = (originalHeight << 16) / thumbnailHeight + 1;
  unsigned char *originalPixels = original->pixels;
  unsigned char *thumbnailPixels = thumbnail->pixels;

  int w, h, pw, ph;
  for (h = 0; h < thumbnailHeight; ++h)
  {
    for (w = 0; w < thumbnailWidth; ++w)
    {
      pw = (w * widthRatio) >> 16;
      ph = (h * heightRatio) >> 16;
      thumbnailPixels[h * thumbnailWidth + w] = originalPixels[ph * originalWidth + pw];
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Review your comand");
    return 2;
  }

  FILE *inputFile = fopen(argv[1], "rb");
  if (inputFile == NULL)
  {
    printf("%s does not exist in this directory.\n", argv[1]);
    return 1;
  }

  Image originalImage;
  readImageData(inputFile, &originalImage);
  readPixels(inputFile, &originalImage);

  fclose(inputFile);

  Image thumbnailImage;
  generateThumbnail(&originalImage, &thumbnailImage);

  FILE *outputFile = fopen("output.pgm", "wb");
  writeImageData(outputFile, thumbnailImage.width, thumbnailImage.height, thumbnailImage.max);
  writePixels(outputFile, thumbnailImage.pixels, thumbnailImage.width * thumbnailImage.height);

  fclose(outputFile);

  free(originalImage.pixels);
  free(thumbnailImage.pixels);

  return 0;
}

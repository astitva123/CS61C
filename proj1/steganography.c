/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	
	Color *color = (Color *)malloc(sizeof(Color));
	int val = 255*((image->image[row][col].B)%2);
	
	color->R = val;
	color->G = val;
	color->B = val;

	return color;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	int rows = image->rows;
	int cols = image->cols;

	Image *result_image = (Image *)malloc(sizeof(Image));
	result_image->rows = rows;
	result_image->cols = cols;

	result_image->image = (Color **)malloc(rows*sizeof(Color *));
	for(int i = 0;i<rows;i++)
	{
		result_image->image[i] = (Color *)malloc(cols*sizeof(Color));
	}

	for(int i = 0;i<rows;i++)
	{
		for(int j = 0;j<cols;j++)
		{
			Color *color = evaluateOnePixel(image, i, j);
			result_image->image[i][j] = *color;
			free(color);
		}
	}

	return result_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc != 2)
	{
		printf("mention source file with the executable\n");
		exit(-1);
	}

	char *filename = argv[1];

	Image *image = readData(filename);
	Image *decoded_image = steganography(image);

	writeData(decoded_image);

	return 0;
}

/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	//YOUR CODE HERE
	Color *color = (Color*)malloc(sizeof(Color));
	int rows = image->rows, cols = image->cols;

	bool alive_red = image->image[row][col].R != 0;
	bool alive_green = image->image[row][col].G != 0;
	bool alive_blue = image->image[row][col].B != 0;

	int alive_red_neighbours = 0;
	int alive_green_neighbours = 0;
	int alive_blue_neighbours = 0;

	for(int i = -1;i<2;i++)
	{
		for(int j = -1;j<2;j++)
		{
			if(i == 0 && j == 0) continue;

			int n_row = row + i;
			int n_col = col + j;

			if(n_row < 0) n_row = rows - 1;
			if(n_row > rows - 1) n_row = 0;

			if(n_col < 0) n_col = cols - 1;
			if(n_col > cols - 1) n_col = 0;

			if(image->image[n_row][n_col].R) alive_red_neighbours++;
			if(image->image[n_row][n_col].G) alive_green_neighbours++;
			if(image->image[n_row][n_col].B) alive_blue_neighbours++;
		}
	}

	int r = image->image[row][col].R;
	int g = image->image[row][col].G;
	int b = image->image[row][col].B;

	color->R = (r>0?r:255)*((rule/(1<<(alive_red*9+alive_red_neighbours)))%2);
	color->G = (g>0?g:255)*((rule/(1<<(alive_green*9+alive_green_neighbours)))%2);
	color->B = (b>0?b:255)*((rule/(1<<(alive_blue*9+alive_blue_neighbours)))%2);

	return color;

}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	//YOUR CODE HERE
	Image *result_image = (Image *)malloc(sizeof(Image));
	int rows = image->rows, cols = image->cols;
	result_image->rows = rows;
	result_image->cols = cols;
	result_image->image = (Color **)malloc(rows*sizeof(Color*));

	for(int i = 0;i<rows;i++)
	{
		result_image->image[i] = (Color *)malloc(cols*sizeof(Color));
	}

	for(int i = 0;i<rows;i++)
	{
		for(int j = 0;j<cols;j++)
		{
			Color *color = evaluateOneCell(image, i, j, rule);
			result_image->image[i][j] = *color;
			free(color);
		}
	}

	return result_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if(argc != 3)
	{
		printf("usage: ./gameOfLife filename rule\nfilename is an ASCII PPM file (type P3) with maximum value 255.\nrule is a hex number beginning with 0x; Life is 0x1808.\n");
		exit(1);
	}

	char *hex_rule = argv[2];
	char *filename = argv[1];

	Image *image = readData(filename);

	uint32_t rule_dec = 0;

	int n =  strlen(hex_rule);
	for(int i = n-1;i>=2;i--)
	{
		rule_dec += (hex_rule[i]-'0')*(pow(16,n-1-i));
	}

	Image* result_image = life(image, rule_dec);
	writeData(result_image);

	free(result_image);
	free(image);

	return 0;
}

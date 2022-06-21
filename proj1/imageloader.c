/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *fptr;
	if(!(fptr = fopen(filename, "r")))
	{
		printf("error opening file\n");
		exit(1);
	}

	int line = 1;
	int rows = 0, cols = 0;
	int ind = -1;
	Image *image = (Image *)malloc(sizeof(Image));

	while(!feof(fptr))
	{
		switch (line)
		{
			case 3:
			{
				int temp;
				fscanf(fptr, "%d", &temp);
				line++;

				break;
			}
			case 1:
			{
				char* temp = malloc(5*sizeof(char));
				fscanf(fptr, "%s", temp);
				free(temp);
				line++;
				
				break;
			}
			case 2:
			{
				if(fscanf(fptr, "%d %d", &cols, &rows) != 2)
				{
					continue;
				}
				
				line++;
				
				image->cols = cols;
				image->rows = rows;
				image->image = (Color **)malloc(rows*sizeof(Color*));
				
				for(int i = 0;i<cols;i++)
				{
					image->image[i] = (Color *)malloc(cols*sizeof(Color));
				}
				
				break;
			}
			default:
			{
				int r = 0;int g = 0;int b = 0;
				if(fscanf(fptr, "%d %d %d", &r, &g, &b) != 3) continue;
				ind++;
				
				int curr_row = ind/cols;
				int curr_col = ind%cols;
				((image->image)[curr_row][curr_col]).R = r;
				((image->image)[curr_row][curr_col]).G = g;
				((image->image)[curr_row][curr_col]).B = b;

				break;
			}
		}
	}

	fclose(fptr);

	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	int rows = image->rows, cols = image->cols;

	printf("P3\n%d %d\n255\n", cols, rows);

	for(int i = 0;i<rows;i++)
	{
		for(int j = 0;j<cols;j++)
		{
			int r = ((image->image)[i][j]).R;
			int g = ((image->image)[i][j]).G;
			int b = ((image->image)[i][j]).B;

			if(r < 10) printf("  %d ", r);
			else if(r < 100) printf(" %d ", r);
			else printf("%d ", r);

			if(g < 10) printf("  %d ", g);
			else if(g < 100) printf(" %d ", g);
			else printf("%d ", g);

			if(j == cols-1)
			{
				if(b < 10) printf("  %d\n", b);
				else if(b < 100) printf(" %d\n", b);
				else printf("%d\n", b);
			}
			else
			{
				if(b < 10) printf("  %d   ", b);
				else if(b < 100) printf(" %d   ", b);
				else printf("%d   ", b);
			}
		}

	}

	// printf("\n");
}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	free(image);
	image = NULL;
}
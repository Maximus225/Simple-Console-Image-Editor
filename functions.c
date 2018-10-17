//By Maxim Johansson

#include "functions.h"

//Function for printing menu
int printMenu() {
	int menuchoice;
	system("cls");
	printf("Program menu\n\n");
	printf("1. Read a picture from file \n");
	printf("2. Save picture to file (local directory) \n");
	printf("3. Invert picture \n");
	printf("4. Color correct the picture \n");
	printf("5. Rotate the picture \n");
	printf("6. Enlarge in the picture\n");
	printf("7. Zoom the picture (crop and set original dimentions)\n");
	printf("8. Exit \n");
	printf("Your choice is: ");
	scanf("%d", &menuchoice);
	getchar();

	return menuchoice;
}
//Function that inverts picture
void invertImg(Image *image)
{

	for (unsigned int i = 0; i < image->height; i++) // COLS
	{
		for (unsigned int j = 0; j < image->width; j++) //ROWS
		{
			image->pixels[i][j].r = 255 - image->pixels[i][j].r; // White - Red
			image->pixels[i][j].g = 255 - image->pixels[i][j].g; // White - Green
			image->pixels[i][j].b = 255 - image->pixels[i][j].b; // White - Blue
		}
	}
}

//Function that color shifts the picture
void colorShift(Image *image) 
{
	for (unsigned int i = 0; i < image->height; i++) //COLS
	{
		for (unsigned int j = 0; j < image->width; j++) //ROWS
		{
			uint8_t tempred = image->pixels[i][j].r;
			uint8_t tempblue = image->pixels[i][j].b;
			uint8_t tempgreen = image->pixels[i][j].g;

			image->pixels[i][j].g = tempred; // Green becomes Red
			image->pixels[i][j].b = tempgreen; // Blue becomes Green
			image->pixels[i][j].r = tempblue; // Red becomes Blue
		}
	}
}

//Function that rotates the picture
void rotateImg(Image *image) 
{

	Image tr; //Temporary rotate
	tr.height = image->width; // Temporary width;
	tr.width = image->height; // Temporary height;

	tr.pixels = (Pixel**)malloc(sizeof(Pixel*)* tr.height); // Allocate HEIGHT

		for (unsigned int i = 0; i < tr.height; i++)
		{
			tr.pixels[i] = (Pixel*)malloc(sizeof(Pixel)* tr.width); //Allocate WIDTH
		}

		for (unsigned int i = 0; i < tr.height; i++)  // COLS
		{
			for (unsigned int j = 0; j < tr.width; j++)  // ROWS
			{
				tr.pixels[i][j].r = image->pixels[j][i].r; 
				tr.pixels[i][j].g = image->pixels[j][i].g;
				tr.pixels[i][j].b = image->pixels[j][i].b;
			}
		}

		for (unsigned int i = 0; i < image->height; i++) // Remove the previous image from the memory
		{   
			free(image->pixels[i]);
		}

		free(image->pixels);

		image->height = tr.height;
		image->width = tr.width;

		image->pixels = (Pixel**)malloc(sizeof(Pixel*)* image->height);

		for (unsigned int i = 0; i < tr.height; i++) 
		{
			image->pixels[i] = (Pixel*)malloc(sizeof(Pixel)* image->width);
		}


		for (unsigned int i = 0; i < image->height; i++)  // COLS
		{
			for (unsigned int j = 0; j < image->width; j++)  // ROWS
			{
				image->pixels[i][j].r = tr.pixels[i][j].r;
				image->pixels[i][j].g = tr.pixels[i][j].g;
				image->pixels[i][j].b = tr.pixels[i][j].b;

			}
		}

		for (unsigned int i = 0; i < tr.height; i++) // Remove the previous image from the memory
		{
			free(tr.pixels[i]);
		}

		free(tr.pixels);
}



//Function that enlarges the picture
void enlargeImg(Image *image)
{
	int mr; // Multiplication ratio
	printf("Please enter a ratio (times): ");
	scanf("%d", &mr);
	getchar();
	Image tcz;
	tcz.width = image->width * mr;
	tcz.height = image->height * mr;

	tcz.pixels = (Pixel**)malloc(sizeof(Pixel*)* tcz.height); //Allocate a new memory

	for (unsigned int i = 0; i < tcz.height; i++)
	{
		tcz.pixels[i] = (Pixel*)malloc(sizeof(Pixel)* tcz.width);

		for (unsigned int j = 0; j < tcz.width; j++)
		{
			tcz.pixels[i][j].r = image->pixels[i / mr][j / mr].r;
			tcz.pixels[i][j].g = image->pixels[i / mr][j / mr].g;
			tcz.pixels[i][j].b = image->pixels[i / mr][j / mr].b;
		}
	}

	for (unsigned int i = 0; i < image->height; i++) // Remove the previous image from the memory
	{
		free(image->pixels[i]);
	}

	free(image->pixels);

	image->height = tcz.height;
	image->width = tcz.width;

	image->pixels = (Pixel**)malloc(sizeof(Pixel*)* image->height);
	for (unsigned int i = 0; i < tcz.height; i++)
	{
		image->pixels[i] = (Pixel*)malloc(sizeof(Pixel)* image->width);

		for (unsigned int j = 0; j < image->width; j++)
		{
			image->pixels[i][j].r = tcz.pixels[i][j].r;
			image->pixels[i][j].g = tcz.pixels[i][j].g;
			image->pixels[i][j].b = tcz.pixels[i][j].b;
		}
	}

	for (unsigned int i = 0; i < tcz.height; i++) // Remove the previous image from the memory
	{
		free(tcz.pixels[i]);
	}

	free(tcz.pixels);

}

//Function that zooms the picture (shall crop and set original height and width)
void zoomImg(Image *image)
{
		int divr1; // Division ratio
		printf("Please enter a ratio (times): ");
		scanf("%d", &divr1);
		getchar();
		Image tz;
		tz.width = image->width / divr1;
		tz.height = image->height / divr1;
		//divr1 = divr1 * 2;

		tz.pixels = (Pixel**)malloc(sizeof(Pixel*)* tz.height); //Allocate a new memory

		for (unsigned int i = 0; i < tz.height; i++)
		{
			tz.pixels[i] = (Pixel*)malloc(sizeof(Pixel)* tz.width);
			
			for (unsigned int j = 0; j < tz.width; j++)
			{
				tz.pixels[i][j].r = image->pixels[(image->height / divr1) + i][(image->width / divr1) + j].r;
				tz.pixels[i][j].g = image->pixels[(image->height / divr1) + i][(image->width / divr1) + j].g;
				tz.pixels[i][j].b = image->pixels[(image->height / divr1) + i][(image->width / divr1) + j].b;

			}
		}

		for (unsigned int i = 0; i < image->height; i++) // Remove the previous image from the memory
		{
			free(image->pixels[i]);
		}

		free(image->pixels);

		image->height = tz.height;
		image->width = tz.width;

		image->pixels = (Pixel**)malloc(sizeof(Pixel*)* image->height);
		for (unsigned int i = 0; i < image->height; i++)
		{
			image->pixels[i] = (Pixel*)malloc(sizeof(Pixel)* image->width);

			for (unsigned int j = 0; j < image->width; j++)
			{
				image->pixels[i][j].r = tz.pixels[i][j].r;
				image->pixels[i][j].g = tz.pixels[i][j].g;
				image->pixels[i][j].b = tz.pixels[i][j].b;
			}
		}

		for (unsigned int i = 0; i < tz.height; i++) // Remove the previous image from the memory
		{
			free(tz.pixels[i]);
		}

		free(tz.pixels);

}

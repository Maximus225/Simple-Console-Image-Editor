////By Maxim Johansson

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "functions.h"
#include <crtdbg.h>
#define HEIGHT 512 //Changable value
#define WIDTH 1024 //Changable value

int main ()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Flag to check for memory leaks

	// Memory allocation & color generation wizardry
    Image plain;
    plain.height = HEIGHT;
    plain.width = WIDTH;
	
	plain.pixels = (Pixel**) malloc(sizeof(Pixel*) * plain.height);
	for(unsigned int i = 0; i < plain.height; i++)
	{
		plain.pixels[i] = (Pixel*) malloc(sizeof(Pixel) * plain.width);
		for(unsigned int j = 0; j < plain.width; j++)
		{
			plain.pixels[i][j].r = 255-(i/2);
			plain.pixels[i][j].g = j/4;
			plain.pixels[i][j].b = 0;
		}
	}

	Image image;
	image.height = HEIGHT;
	image.width = WIDTH;

	// Variable declarations.

	bool filenamematch = false; // Boolean to loop the match.
	bool fileisloaded = false; // Boolean to loop the match.
	int choicereturn; // A returned choice from printMenu().
	char readfilename[30]; // For scanning the flie name.
	char newfilename[30]; // For scanning the flie name.
	image.pixels = NULL; // Free the memory

	// Program menu.
do {
		choicereturn = printMenu();
		switch (choicereturn)
		{
		case 1:
			do
			{
				printf("\nType the name of the file: ");
				scanf("%s", &readfilename);
				getchar();

				FILE *filepointer; // Extra feature to access file system.

					if ((filepointer = fopen(readfilename, "r")) == NULL) // This will check the file existance before importing.
					{
						filenamematch = false;
						printf("\nThe file wasn't found, please try again. ");
					}

					else if (image.pixels != NULL) // This will reimport the file (replace).
					{

						for (unsigned int i = 0; i < image.height; i++) //Will go though and empty
						{
							free(image.pixels[i]);
						}

						free(image.pixels); // Will just empty and import the file,
						fclose(filepointer);
						filenamematch = true;
						fileisloaded = true;
						readImage(readfilename, &image);
						printf("\nThe picture has been reimported! \nPress any key to continue...");
						getchar();
					}

					else // This will import the file.
					{
						fclose(filepointer);
						filenamematch = true;
						fileisloaded = true;
						readImage(readfilename, &image);
						printf("\nThe picture has been imported! \nPress any key to continue...");
						getchar();
					}

			} while (filenamematch != true);
			break;

		case 2:
			if (image.pixels != NULL)
			{
				printf("Note: name must have no spaces and .png extention must presist. \nUsing the same name with already existing file, will replace that file \nType the name: ");
				scanf("%s", &newfilename);
				getchar();
				printf("\nSaving PNG...\n");
				writeImage(newfilename, &image);
				printf("Save complete! \nPress any key to continue...");
				getchar();
			}
			else
			{
					printf("There is nothing to save! Load the file first!\n");
					printf("Press any key to continue...");
					getchar();
			}
			break;

		case 3:
			if (image.pixels != NULL)
			{
				invertImg(&image);
				printf("The picture has been inverted! \nPress any key to continue...");
				getchar();
			}
			else
			{ 
				printf("Connot comply, load the file first!\n");
				printf("Press any key to continue...");
				getchar();
			}
			break;

		case 4:
			if (image.pixels != NULL)
			{
				colorShift(&image);
				printf("The picture has been color corrected! \nPress any key to continue...");
				getchar();
				
			}
			else
			{
				printf("Connot comply, load the file first!\n");
				printf("Press any key to continue...");
				getchar();
			}
			break;

		case 5:
			if (image.pixels != NULL)
			{
				rotateImg(&image);
				printf("The picture has been rotated! \nPress any key to continue...");
				getchar();
			}
			else
			{
				printf("Connot comply, load the file first!\n");
				printf("Press any key to continue...");
				getchar();
			}
			break;

		case 6:
			if (image.pixels != NULL)
			{
				enlargeImg(&image);
				printf("The picture has been enlarged! \nPress any key to continue...");
				getchar();
			}
			else
			{
				printf("Connot comply, load the file first!\n");
				printf("Press any key to continue...");
				getchar();
			}
			break;

		case 7:
			if (image.pixels != NULL)
			{
				zoomImg(&image);
				printf("The picture has been zoomed in! \nPress any key to continue...");
				getchar();
			}
			else
			{ 
				printf("Connot comply, load the file first!\n");
				printf("Press any key to continue...");
				getchar();
			}
			break;

		case 8:
			// That will check if picture was loaded before and if yes, will free the memory and close the program, else just close the program.
			if (image.pixels != NULL)
			{
				for (unsigned int i = 0; i < image.height; i++) // Will go though and empty
				{
					free(image.pixels[i]);
				}
				free(image.pixels);

				for (unsigned int i = 0; i < plain.height; i++) // Will go though and empty
				{
					free(plain.pixels[i]);
				}
				free(plain.pixels);
			}

			else
			{

				for (unsigned int i = 0; i < plain.height; i++) // Will go though and empty
				{
					free(plain.pixels[i]);
				}
				free(plain.pixels);
			}

			break;
		}

	} while (choicereturn != 8);
	return 0;
}

/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gImageSurface = nullptr;


bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Load Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gImageSurface = SDL_LoadBMP("02_load_image/sdl_image.bmp");
	if (gImageSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_load_image/sdl_image.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gImageSurface);
	gImageSurface = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{

	if (!init())
	{
		printf("Failed to Initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to Load Media!\n");
		}
		else
		{
			bool quit = false;
			SDL_Event evt;
			while (!quit)
			{
				while (SDL_PollEvent(&evt) != 0)
				{
					if (evt.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				SDL_BlitSurface(gImageSurface, nullptr, gScreenSurface, nullptr);
				SDL_UpdateWindowSurface(gWindow);
			}

		}

	}
	
	close();

	return 0;
}

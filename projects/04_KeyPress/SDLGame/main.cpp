/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
SDL_Surface* gCurrentSurface = nullptr;
SDL_Surface* gkeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];


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

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image: %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	return loadedSurface;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gkeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("images/press.bmp");
	if (gkeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image: %s", SDL_GetError());
		success = false;
	}

	gkeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("images/up.bmp");
	if (gkeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image: %s", SDL_GetError());
		success = false;
	}

	gkeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("images/down.bmp");
	if (gkeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image: %s", SDL_GetError());
		success = false;
	}

	gkeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("images/left.bmp");
	if (gkeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image: %s", SDL_GetError());
		success = false;
	}

	gkeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("images/right.bmp");
	if (gkeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image: %s", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface



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

			gCurrentSurface = gkeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

			while (!quit)
			{
				while (SDL_PollEvent(&evt) != 0)
				{
					if (evt.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (evt.type == SDL_KEYDOWN)
					{
						switch (evt.key.keysym.sym)
						{
							case SDLK_UP:
							gCurrentSurface = gkeyPressSurfaces[KEY_PRESS_SURFACE_UP];
							break;

							case SDLK_DOWN:
							gCurrentSurface = gkeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
							break;

							case SDLK_LEFT:
							gCurrentSurface = gkeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gkeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
							break;

							default:
							gCurrentSurface = gkeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
							break;
						}
					}
				}

				SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
				SDL_UpdateWindowSurface(gWindow);
			}

		}

	}
	
	close();

	return 0;
}

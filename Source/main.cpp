#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <direct.h>
#define getcwd _getcwd
#endif

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <unistd.h>
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(__linux__)
#include <unistd.h>
#endif

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <sstream>

using namespace std;

#include "player.h"

//code for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;
int timer = 0;

//game running
bool gameRunning = true;

int playerHitPoints = 3;

//create the SDL_Rectangle for the textures position and size - x,y,w,h
SDL_Rect backgroundPos;

//cursor float vars for moement
float pos_X, pos_Y;

float X_pos = 0.0f;
float Y_pos = 0.0f;

#include <vector>

#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {

//cout to show we are running on Windows
#if defined(_WIN32) || (_WIN64)
	cout << "Running on Windows" << endl;
	//string var to hold the current working directory on __APPLE__
	string currentWorkingDirectory(getcwd(NULL, 0));
	//create a string to link to the images folder on __APPLE__
	string images_dir = currentWorkingDirectory + "\\PiedPiperResource\\Images\\";
	string audio_dir = currentWorkingDirectory + "\\PiedPiperResource\\Audio\\";
#endif

//cout to show that we are running on Linux
#if defined(__linux__)
	cout << "Running on Linux" << endl;
	cout << "Added on Linux" << endl;
	//string var to hold the current working directory on __APPLE__
	string currentWorkingDirectory(getcwd(NULL, 0));
	//create a string to link to the images folder on __APPLE__
	string images_dir = currentWorkingDirectory + "/PiedPiperResource/Images/";
	string audio_dir = currentWorkingDirectory + "/PiedPiperResource/Audio/";
#endif

//cout to show that we are running on Apple
#if defined(__APPLE__)
	cout << "Running on Apple" << endl;
	//string var to hold the current working directory on __APPLE__
	string currentWorkingDirectory(getcwd(NULL,0));
	//create a string to link to the images folder on __APPLE__
	string images_dir = currentWorkingDirectory +"/PiedPiperResource/Images/";
	string audio_dir = currentWorkingDirectory + "/PiedPiperResource/Audio/";
#endif

    SDL_Window *window;                    // Declare a pointer
    SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        1024,                               // width, in pixels
        768,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL)
    {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    //Create a Renderer variable - pointer
    SDL_Renderer *renderer = NULL;

    //create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //////////////////////////////////////////////////////////////////////////////////
    //create the background
    //create a SDL surface to hold the background image
    SDL_Surface *surface = IMG_Load((images_dir + "scene_1.png").c_str());

    //create a SDL texture
    SDL_Texture *background;

    //place surface info into the texture bkdg1
    background = SDL_CreateTextureFromSurface(renderer,surface);

    ////free the SDL surface
    SDL_FreeSurface(surface);

    //set the X,Y,W, and H for the Rectangle
    backgroundPos.x = 0;
    backgroundPos.y = 0;
    backgroundPos.w = 1024;
    backgroundPos.h = 768;

    //////////////////////////////////////////////////////////////////////////////////

	//***** SDL Event to handle input *****
	SDL_Event event;

	//create player
	Player player = Player(renderer, 0, images_dir.c_str(), audio_dir.c_str(),50.0f, 618.0f);

    // The window is open: could enter program loop here (see SDL_PollEvent())
	while(gameRunning == true)
	{
		//set up frame rate for the section, or CASE
		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime - lastTime)/1000;
		lastTime = thisTime;

		//check for input events
		if(SDL_PollEvent(&event))
		{
			//check to see if the SDL Window is closed - player clicks X in window
			if(event.type == SDL_QUIT)
			{
				gameRunning = false;
				break;
			}
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
				//case keyboardmovement
				case SDLK_ESCAPE:
					gameRunning = false;
				break;
				//move right
				case SDLK_RIGHT:
					player.moveRight = true;
					player.moveX += 5;
				break;
				//move left
				case SDLK_LEFT:
					player.moveLeft = true;
					//player.moveX--;
				break;

				}
			}
		}

		//update player
		player.Update(deltaTime);

		//draw section
		//clear the SDL rendertarget
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background ,NULL, &backgroundPos);

		//draw player
		player.Draw(renderer);


		SDL_RenderPresent(renderer);

	}
    //SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}


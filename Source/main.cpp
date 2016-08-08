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

//enemy alive
bool eAlive = true;
bool pAlive = true;
bool enemyDead = false;

int playerHitPoints = 3;
int ammoCount = 10;

//rotate images
float rotatePic;

//create the SDL_Rectangle for the textures position and size - x,y,w,h
SDL_Rect backgroundPos;

// Create a SDL Rectangle for the roomTexture's position and size
SDL_Rect turretPos;

// Create a SDL Rectangle for the roomTexture's position and size
SDL_Rect eBulletPos;

// Create a SDL Rectangle for the roomTexture's position and size
SDL_Rect pBulletPos;

// Create a SDL Rectangle for the roomTexture's position and size
SDL_Rect deathPos;

//center of the image to rotate
SDL_Point center;

//cursor float vars for moement
float pos_X, pos_Y;

float X_pos = 0.0f;
float Y_pos = 0.0f;

float timeReset = 0;

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

	// ******************* Create the turret texture - START *******************

	//create a SDL surface to hold the background image
	SDL_Surface *surface2 = IMG_Load((images_dir + "enemyWizard.png").c_str());
	SDL_Surface *surface2Hit = IMG_Load((images_dir + "enemyWizardHit.png").c_str());
	SDL_Surface *surface2Dead = IMG_Load((images_dir + "enemyWizardDead.png").c_str());
	SDL_Surface *surface2Hit2 = IMG_Load((images_dir + "enemyWizardHit2.png").c_str());
	
	// SDL Texture
	SDL_Texture *turret2;
	SDL_Texture *turret2Hit;
	SDL_Texture *turret2Dead;
	SDL_Texture *turret2Hit2;

	//place surface info into the texture bkdg1
	turret2 = SDL_CreateTextureFromSurface(renderer, surface2);
	turret2Hit = SDL_CreateTextureFromSurface(renderer, surface2Hit);
	turret2Dead = SDL_CreateTextureFromSurface(renderer, surface2Dead);
	turret2Hit2 = SDL_CreateTextureFromSurface(renderer, surface2Hit2);

	//free the SDL surface
	SDL_FreeSurface(surface2);
	SDL_FreeSurface(surface2Hit);
	SDL_FreeSurface(surface2Dead);
	SDL_FreeSurface(surface2Hit2);

	// Set the x, y, width and height SDL Rectangle values
	turretPos.x = 650;
	turretPos.y = 618;
	turretPos.w = 50;
	turretPos.h = 50;

	// ******************* Create the turret texture - END *******************
	// ******************* Create the enemy bullet texture - START *******************

	//create a SDL surface to hold the background image
	SDL_Surface *surface3 = IMG_Load((images_dir + "enemyBullet.png").c_str());

	// SDL Texture
	SDL_Texture *eBullet;

	// load the image into the texture
	eBullet = SDL_CreateTextureFromSurface(renderer, surface3);

	//free the SDL surface
	SDL_FreeSurface(surface3);

	// Set the x, y, width and height SDL Rectangle values
	eBulletPos.x = -200;
	eBulletPos.y = -200;
	eBulletPos.w = 16;
	eBulletPos.h = 16;

	// ******************* Create the enemy bullet texture - END *******************
	// ******************* Create the player bullet texture - START *******************

	//create a SDL surface to hold the background image
	SDL_Surface *surface4 = IMG_Load((images_dir + "playerBullet.png").c_str());

	// SDL Texture
	SDL_Texture *playerBullet;

	// load the image into the texture
	playerBullet = SDL_CreateTextureFromSurface(renderer, surface4);

	//free the SDL surface
	SDL_FreeSurface(surface4);

	// Set the x, y, width and height SDL Rectangle values
	pBulletPos.x = -100;
	pBulletPos.y = -100;
	pBulletPos.w = 16;
	pBulletPos.h = 16;

	// ******************* Create the player bullet texture - END *******************

	// ******************* Create the death texture - START *******************

	//create a SDL surface to hold the background image
	SDL_Surface *surface5 = IMG_Load((images_dir + "deathScreen.png").c_str());

	// SDL Texture
	SDL_Texture *deathScreen;

	// load the image into the texture
	deathScreen = SDL_CreateTextureFromSurface(renderer, surface5);

	//free the SDL surface
	SDL_FreeSurface(surface5);

	// Set the x, y, width and height SDL Rectangle values
	deathPos.x = 0;
	deathPos.y = 0;
	deathPos.w = 1024;
	deathPos.h = 768;

	// ******************* Create the deat texture - END *******************

	//***** SDL Event to handle input *****
	SDL_Event event;

	// boolean to see if the turret is active
	bool turretActive = false;

	//basic vars for simple player(p)/enemy(e) bullet fire with 1 bullet each
	bool eBulletActive = true;
	bool pBulletActive = true;

	int eBulletDir = 0;
	int pBulletDir = 0;

	// vars for playerHealth and bullet health
	//int pHealth = 10;
	int eHealth = 1;

	//init random number seed
	srand(time(NULL));

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
		while(SDL_PollEvent(&event) != 0)
		{
			//check to see if the SDL Window is closed - player clicks X in window
			if(event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
			else {
				if (event.type == SDL_KEYDOWN && event.key.repeat == 0)//key pressed
				{
					switch (event.key.keysym.sym)
					{
						//case keyboardmovement
					case SDLK_ESCAPE:
						gameRunning = false;
						break;
						//move right
					case SDLK_RIGHT:
						player.playerVelocityX += player.playerSpeed;
						break;
						//move left
					case SDLK_LEFT:
						player.playerVelocityX -= player.playerSpeed;
						break;
						// Check to see if the player fired
					case SDLK_SPACE:
						// check to see if bullet is not already active
						if (pBulletActive == false && player.ammoCount > 0)
						{
							player.ammoCount -= 1;
							// move to player's position
							pBulletPos.x = player.playerPos.x;
							pBulletPos.y = (player.playerPos.y + (player.playerPos.h / 2) - 20);

							// check to see if the player is to the left or right of the turret and set the
							// player's bulletDir as needed
							if (player.playerPos.x < turretPos.x) {
								pBulletDir = 10;
							}
							else {
								pBulletDir = -10;
							}
							// active bullet
							pBulletActive = true;
							player.threw = true;
						}
						break;
					}
				}
				else if (event.type == SDL_KEYUP && event.key.repeat == 0)//key released
				{
					switch (event.key.keysym.sym)
					{
						//move right
					case SDLK_RIGHT:
						player.playerVelocityX -= player.playerSpeed;
						break;
						//move left
					case SDLK_LEFT:
						player.playerVelocityX += player.playerSpeed;
						break;
					}
				}
			}
		}

		center.x = eBulletPos.w/2;
		center.y = eBulletPos.h/2;

		if(enemyDead == true)
		{
			timeReset += 1;
		}else{
			timeReset = 0;
		}

		//update player
		player.Update(deltaTime);

		rotatePic += 15;

		//check the distance to player
		double distancex = ((turretPos.x + (turretPos.w / 2))
			- (player.playerPos.x + (player.playerPos.w / 2)))
			* ((turretPos.x + (turretPos.w / 2))
				- (player.playerPos.x + (player.playerPos.w / 2)));
		double distancey = (turretPos.y - player.playerPos.y)
			* (turretPos.y - player.playerPos.y);

		double calcdistance = sqrt(distancex + distancey);

		if (eAlive == true)
		{
			if (calcdistance <= 425) {
				//cout << "Turret is active" << endl;

				turretActive = true;

				//random number 1 - 10 (higher number, slower fire rate
				int random_number = std::rand() % 50;

				// check to see if bullet is not already active and random number equals 5
				if ((eBulletActive) == false && (random_number == 5)) {

					// move to player's position
					eBulletPos.x = turretPos.x;
					eBulletPos.y = (turretPos.y + (turretPos.h / 2));

					// check to see if the player is to the left or right of the turret and set the
					// player's bulletDir as needed
					if (player.playerPos.x < turretPos.x) {
						eBulletDir = -5;
					}
					else {
						eBulletDir = 5;
					}
					// active bullet
					eBulletActive = true;
				}

			}
			else {
				//cout << "Turret is not active" << endl;

				turretActive = false;
			}
		}

		//if the enemy bullet is active - update
		if (eBulletActive) {
			eBulletPos.x += eBulletDir;
		}

		// check for off screen - LEFT or RIGHT
		if (eBulletPos.x > 1024 || eBulletPos.x < 0) {
			eBulletActive = false;
			eBulletPos.x = -200;
			eBulletPos.y = -200;
			eBulletDir = 0;
		}

		//if the player bullet is active - update
		if (pBulletActive) {
			pBulletPos.x += pBulletDir;
		}

		// check for off screen - LEFT or RIGHT
		if (pBulletPos.x > 1024 || pBulletPos.x < 0) {
			pBulletActive = false;
			pBulletPos.x = -100;
			pBulletPos.y = -100;
			pBulletDir = 0;
		}

		// **** UPDATE Bullets if active - END *********

		// ******************* COLLISION CHECK - START *******************
		// Check for player collision with turret bullet
		if (SDL_HasIntersection(&player.playerPos, &eBulletPos) && eAlive == true) {

			//reset enemy bullet
			eBulletActive = false;
			eBulletPos.x = -200;
			eBulletPos.y = -200;
			eBulletDir = 0;

			//subtract player health
			player.playerHealth -= 1;
			//cout << pHealth << endl;
		}

		// Check for turret collision with player bullet while active
		if (SDL_HasIntersection(&turretPos, &pBulletPos) && turretActive == true && eAlive == true) {

			//reset player bullet
			player.threw = false;
			pBulletActive = false;
			pBulletPos.x = -200;
			pBulletPos.y = -200;
			pBulletDir = 0;

			//subtract player health
			eHealth -= 1;
			cout << eHealth << endl;
		}

		// Check for turret collision with player bullet while NOT active
		if (SDL_HasIntersection(&turretPos, &pBulletPos) && turretActive == false && eAlive == true) {

			//reset player bullet
			player.threw = false;
			pBulletActive = false;
			pBulletPos.x = -200;
			pBulletPos.y = -200;
			pBulletDir = 0;
		}

		if (eHealth <= 0)
		{
			eAlive = false;
		}

		if (player.playerHealth <= 0)
		{
			pAlive = false;
		}

		cout << timeReset << endl;

		//draw section
		//clear the SDL rendertarget
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background ,NULL, &backgroundPos);

		//draw enemy bullet if active
		if (eBulletActive && eAlive == true && pAlive == true) {
			SDL_RenderCopyEx(renderer, eBullet, NULL, &eBulletPos, rotatePic, &center, SDL_FLIP_NONE);
		}

		//draw player bullet if active
		if (pBulletActive && pAlive == true) {
			SDL_RenderCopyEx(renderer, playerBullet, NULL, &pBulletPos, rotatePic, &center, SDL_FLIP_NONE);
		}

		//check enemy health 
		if (eHealth > 0)
		{
			//draw enemy 
			SDL_RenderCopy(renderer, turret2, NULL, &turretPos);
		}else if(eHealth <= 0)
		{
			enemyDead = true;
			if(timeReset <= 15){
				SDL_RenderCopy(renderer, turret2Hit, NULL, &turretPos);
			}else if(timeReset <= 35)
			{
				SDL_RenderCopy(renderer, turret2Hit2, NULL, &turretPos);
			}else{
				SDL_RenderCopy(renderer, turret2Dead, NULL, &turretPos);
			}
			turretActive = false;
		}

		if (pAlive == true) {
					//draw player
					player.Draw(renderer);
				}
				else {
					SDL_RenderCopy(renderer, deathScreen, NULL, &deathPos);
				}

		SDL_RenderPresent(renderer);

		// Delay so that we are at 60 FPS
		SDL_Delay(16);

	}
    //SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}


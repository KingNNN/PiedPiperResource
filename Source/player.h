//needed includes
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#include <vector>

#if defined(__APPLE__)
	#include "SDL2/SDL.h"
	#include "SDL2_image/SDL_image.h"
	#include "SDL2_mixer/SDL_mixer.h"
	#include "SDL2_ttf/SDL_ttf.h"
#endif

#if defined(_WIN32) || (_WIN64)
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif

#if defined(__linux__)
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_image.h"
    #include "SDL2/SDL_mixer.h"
    #include "SDL2/SDL_ttf.h"
#endif


class Player{

public:

	//textures for health bar
	SDL_Texture *health5, *health4, *health3, *health2, *health1, *health_Background;

	//rectangles for the health bar images
	SDL_Rect health5_Rect, health4_Rect, health3_Rect, health2_Rect, health1_Rect, health_Background_Rect;

	//textures for ammo bar
	SDL_Texture *ammo10, *ammo9, *ammo8, *ammo7, *ammo6, *ammo5, *ammo4, *ammo3, *ammo2, *ammo1, *ammo0, *ammo_Background;

	//rectangles for the health bar images
	SDL_Rect ammo10_Rect, ammo9_Rect, ammo8_Rect, ammo7_Rect, ammo6_Rect, ammo5_Rect, ammo4_Rect, ammo3_Rect, ammo2_Rect, ammo1_Rect, ammo0_Rect, ammo_Background_Rect;

	//textures for flag
	SDL_Texture *flag, *flag_Background;

	//rectangles for the flag images
	SDL_Rect flag_Rect, flag_Background_Rect;

	//textures for key
	SDL_Texture *key, *key_Background;

	//rectangles for the key images
	SDL_Rect key_Rect, key_Background_Rect;

	//player health
	float playerHealth, maxHealth;

	//string to hold the path to the player's texture
	string playerPath;

	//integer for the player's number
	int playerNum;

	//player's texture to hold img
	SDL_Texture *texture;

	//player's SDL_Rect for the X, Y, W, and H of texture
	SDL_Rect posRect;

	//floats to hold the hoystick axis(-1 or 0 or 1)
	float xDir, xDirOld;
	float yDir, yDirOld;

	//float for player speed
	float speed;

	//float for the player's position to avoid precisou loss
	float moveX, moveY;

	bool moveRight;
	bool moveLeft;

	//add x and y values
	Sint16 Xvalue, Yvalue;

	//player angle
	float playerAngle;

	int getTime;

	//player speed
	float playerSpeed;

	//player ammo count
	int ammoCount;

	//point that will be used to rotate the it - relative to teh center
	SDL_Point center;

	//player's creation method using passed in values for renderer, player number, path to the texture starting position X, starting position Y
	Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y);

	//update the player using the passed in deltaTIme
	void Update(float deltaTime);

	//draw the player main's passed in renderer
	void Draw(SDL_Renderer *renderer);

private:


};

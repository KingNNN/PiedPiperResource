#include "player.h"

Player::Player(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{
	//loat health GUI
	health5 = IMG_LoadTexture(renderer, (filePath + "health_5.png").c_str());
	health4 = IMG_LoadTexture(renderer, (filePath + "health_4.png").c_str());
	health3 = IMG_LoadTexture(renderer, (filePath + "health_3.png").c_str());
	health2 = IMG_LoadTexture(renderer, (filePath + "health_2.png").c_str());
	health1 = IMG_LoadTexture(renderer, (filePath + "health_1.png").c_str());
	health_Background = IMG_LoadTexture(renderer, (filePath + "health_background.png").c_str());
	ammo10 = IMG_LoadTexture(renderer, (filePath + "ammo_10.png").c_str());
	ammo_Background = IMG_LoadTexture(renderer, (filePath + "ammo_background.png").c_str());
	flag = IMG_LoadTexture(renderer, (filePath + "flag.png").c_str());
	flag_Background = IMG_LoadTexture(renderer, (filePath + "flag_background.png").c_str());
	key = IMG_LoadTexture(renderer, (filePath + "key.png").c_str());
	key_Background = IMG_LoadTexture(renderer, (filePath + "key_background.png").c_str());

	health_Background_Rect.x = health5_Rect.x = health4_Rect.x = health3_Rect.x = health2_Rect.x = health1_Rect.x = 5;
	health_Background_Rect.y = health5_Rect.y = health4_Rect.y = health3_Rect.y = health2_Rect.y = health1_Rect.y = 3;
	health_Background_Rect.w = health5_Rect.w = health4_Rect.w = health3_Rect.w = health2_Rect.w = health1_Rect.w = 200;
	health_Background_Rect.h= health5_Rect.h = health4_Rect.h = health3_Rect.h = health2_Rect.h = health1_Rect.h = 50;

	ammo_Background_Rect.x = ammo10_Rect.x = 615;
	ammo_Background_Rect.y = ammo10_Rect.y = 700;
	ammo_Background_Rect.w = ammo10_Rect.w = 400;
	ammo_Background_Rect.h = ammo10_Rect.h = 60;

	flag_Background_Rect.x = flag_Rect.x = 960;
	flag_Background_Rect.y = flag_Rect.y = 10;
	flag_Background_Rect.w = flag_Rect.w = 50;
	flag_Background_Rect.h = flag_Rect.h = 50;

	key_Background_Rect.x = key_Rect.x = 10;
	key_Background_Rect.y = key_Rect.y = 710;
	key_Background_Rect.w = key_Rect.w = 50;
	key_Background_Rect.h = key_Rect.h = 50;

	//player health
	playerHealth = 5.0f;
	maxHealth = 100.0f;

	//set float for player speed
	speed = 200.0f;

	//player path to image
	playerPath = filePath + "player.png";

	//loat the surface into the texture
	texture = IMG_LoadTexture(renderer, playerPath.c_str());

	//set the SDL_Rect X and Y for the player
	posRect.x = x;
	posRect.y = y;

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	posRect.w = w;
	posRect.h = h;

	//set the movement floats to the players original X and Y
	pos_X = x;
	pos_Y = y;

	//set the xDir and yDIr for the joysticks
	xDir = 0;
	yDir = 0;

	//set the initial values so that Player can shoot
	xDirOld = 1;
	yDirOld = 0;

	//center of the image rectangle
	center.x = posRect.w/2;
	center.y = posRect.h/2;
}

void Player::Draw(SDL_Renderer *renderer)
{
	//draw the player texture using the vars texture and posRect
	SDL_RenderCopyEx(renderer, texture, NULL, &posRect, playerAngle, &center, SDL_FLIP_NONE);
	SDL_RenderCopy(renderer, health5, NULL, &health5_Rect);
	SDL_RenderCopy(renderer, health4, NULL, &health4_Rect);
	SDL_RenderCopy(renderer, health3, NULL, &health3_Rect);
	SDL_RenderCopy(renderer, health2, NULL, &health2_Rect);
	SDL_RenderCopy(renderer, health1, NULL, &health1_Rect);
	SDL_RenderCopy(renderer, ammo10, NULL, &ammo10_Rect);
	SDL_RenderCopy(renderer, flag, NULL, &flag_Rect);
	SDL_RenderCopy(renderer, key, NULL, &key_Rect);

}

void Player::Update(float deltaTime)
{
	if(posRect.x < 0)
	{
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if(posRect.x > 1024 - posRect.w)
	{
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}
}


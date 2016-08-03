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
	ammo9 = IMG_LoadTexture(renderer, (filePath + "ammo_9.png").c_str());
	ammo8 = IMG_LoadTexture(renderer, (filePath + "ammo_8.png").c_str());
	ammo7 = IMG_LoadTexture(renderer, (filePath + "ammo_7.png").c_str());
	ammo6 = IMG_LoadTexture(renderer, (filePath + "ammo_6.png").c_str());
	ammo5 = IMG_LoadTexture(renderer, (filePath + "ammo_5.png").c_str());
	ammo4 = IMG_LoadTexture(renderer, (filePath + "ammo_4.png").c_str());
	ammo3 = IMG_LoadTexture(renderer, (filePath + "ammo_3.png").c_str());
	ammo2 = IMG_LoadTexture(renderer, (filePath + "ammo_2.png").c_str());
	ammo1 = IMG_LoadTexture(renderer, (filePath + "ammo_1.png").c_str());
	ammo0 = IMG_LoadTexture(renderer, (filePath + "ammo_0.png").c_str());
	ammo_Background = IMG_LoadTexture(renderer, (filePath + "ammo_background.png").c_str());
	flag = IMG_LoadTexture(renderer, (filePath + "flag.png").c_str());
	flag_Background = IMG_LoadTexture(renderer, (filePath + "flag_background.png").c_str());
	key = IMG_LoadTexture(renderer, (filePath + "key.png").c_str());
	key_Background = IMG_LoadTexture(renderer, (filePath + "key_background.png").c_str());

	health_Background_Rect.x = health5_Rect.x = health4_Rect.x = health3_Rect.x = health2_Rect.x = health1_Rect.x = 5;
	health_Background_Rect.y = health5_Rect.y = health4_Rect.y = health3_Rect.y = health2_Rect.y = health1_Rect.y = 3;
	health_Background_Rect.w = health5_Rect.w = health4_Rect.w = health3_Rect.w = health2_Rect.w = health1_Rect.w = 200;
	health_Background_Rect.h= health5_Rect.h = health4_Rect.h = health3_Rect.h = health2_Rect.h = health1_Rect.h = 50;

	ammo_Background_Rect.x = ammo10_Rect.x = ammo9_Rect.x = ammo8_Rect.x = ammo7_Rect.x = ammo6_Rect.x = ammo5_Rect.x = ammo4_Rect.x = ammo3_Rect.x = ammo2_Rect.x = ammo1_Rect.x = ammo0_Rect.x = 615;
	ammo_Background_Rect.y = ammo10_Rect.y = ammo9_Rect.y = ammo8_Rect.y = ammo7_Rect.y = ammo6_Rect.y = ammo5_Rect.y = ammo4_Rect.y = ammo3_Rect.y = ammo2_Rect.y = ammo1_Rect.y = ammo0_Rect.y =700;
	ammo_Background_Rect.w = ammo10_Rect.w = ammo9_Rect.w = ammo8_Rect.w = ammo7_Rect.w = ammo6_Rect.w = ammo5_Rect.w = ammo4_Rect.w = ammo3_Rect.w = ammo2_Rect.w = ammo1_Rect.w = ammo0_Rect.w =400;
	ammo_Background_Rect.h = ammo10_Rect.h = ammo9_Rect.h = ammo8_Rect.h = ammo7_Rect.h = ammo6_Rect.h = ammo5_Rect.h = ammo4_Rect.h = ammo3_Rect.h = ammo2_Rect.h = ammo1_Rect.h = ammo0_Rect.h = 60;

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

	//set player bullet count to max
	ammoCount = 10;

	moveRight = false;
	moveLeft = false;

	//player path to image
	playerPath = filePath + "player.png";

	//loat the surface into the texture
	texture = IMG_LoadTexture(renderer, playerPath.c_str());

	//set the SDL_Rect X and Y for the player
	playerPos.x = x;
	playerPos.y = y;

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	playerPos.w = w;
	playerPos.h = h;

	//set the movement floats to the players original X and Y
	moveX = x;
	moveY = y;

	//set the initial values so that Player can shoot
	xDirOld = 1;
	yDirOld = 0;

	//center of the image rectangle
	center.x = playerPos.w/2;
	center.y = playerPos.h/2;

	//player speed
	playerSpeed = 1;

	//set the velocity of the player
	playerVelocityX = 0;
	playerVelocityY = 0;

}

void Player::Draw(SDL_Renderer *renderer)
{
	//draw the player texture using the vars texture and posRect
	SDL_RenderCopyEx(renderer, texture, NULL, &playerPos, playerAngle, &center, SDL_FLIP_NONE);

	//display player health
	if(playerHealth == 5)
	{
		SDL_RenderCopy(renderer, health5, NULL, &health5_Rect);
	}
	if(playerHealth == 4)
	{
		SDL_RenderCopy(renderer, health4, NULL, &health4_Rect);
	}
	if(playerHealth == 3)
	{
		SDL_RenderCopy(renderer, health3, NULL, &health3_Rect);
	}
	if(playerHealth == 2)
	{
		SDL_RenderCopy(renderer, health2, NULL, &health2_Rect);
	}
	if(playerHealth == 1)
	{
		SDL_RenderCopy(renderer, health1, NULL, &health1_Rect);
	}

	//display ammo count
	if(ammoCount == 10)
	{
		SDL_RenderCopy(renderer, ammo10, NULL, &ammo10_Rect);
	}
	if(ammoCount == 9)
	{
		SDL_RenderCopy(renderer, ammo9, NULL, &ammo9_Rect);
	}
	if(ammoCount == 8)
	{
		SDL_RenderCopy(renderer, ammo8, NULL, &ammo8_Rect);
	}
	if(ammoCount == 7)
	{
		SDL_RenderCopy(renderer, ammo7, NULL, &ammo7_Rect);
	}
	if(ammoCount == 6)
	{
		SDL_RenderCopy(renderer, ammo6, NULL, &ammo6_Rect);
	}
	if(ammoCount == 5)
	{
		SDL_RenderCopy(renderer, ammo5, NULL, &ammo5_Rect);
	}
	if(ammoCount == 4)
	{
		SDL_RenderCopy(renderer, ammo4, NULL, &ammo4_Rect);
	}
	if(ammoCount == 3)
	{
		SDL_RenderCopy(renderer, ammo3, NULL, &ammo3_Rect);
	}
	if(ammoCount == 2)
	{
		SDL_RenderCopy(renderer, ammo2, NULL, &ammo2_Rect);
	}
	if(ammoCount == 1)
	{
		SDL_RenderCopy(renderer, ammo1, NULL, &ammo1_Rect);
	}
	if(ammoCount == 0)
	{
		SDL_RenderCopy(renderer, ammo0, NULL, &ammo0_Rect);
	}

	SDL_RenderCopy(renderer, flag, NULL, &flag_Rect);
	SDL_RenderCopy(renderer, key, NULL, &key_Rect);

}

void Player::Update(float deltaTime)
{
	playerPos.x += playerVelocityX;
//	if(posRect.x < 0)
//	{
//		posRect.x = 0;
//		pos_X = posRect.x;
//	}
//
//	if(posRect.x > 1024 - posRect.w)
//	{
//		posRect.x = 1024 - posRect.w;
//		pos_X = posRect.x;
//	}
//
//	if(posRect.y < 0)
//	{
//		posRect.y = 0;
//		pos_Y = posRect.y;
//	}
//
//	if(posRect.y > 768 - posRect.h)
//	{
//		posRect.y = 768 - posRect.h;
//		pos_Y = posRect.y;
//	}
}


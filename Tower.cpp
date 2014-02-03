#include "Tower.h"


Tower::Tower()
{}


Tower::Tower(int type_tower) : type(type_tower)
{
	SDL_Rect pos = { 0, 105 };

	if (type_tower == 1)
	{
		SDL_Surface *enemy_1 = IMG_Load("image/tower_1.png");
		SDL_Rect frame1 = { 0 * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK };

		image = enemy_1;
		current_frame = frame1;
	}
	else if (type_tower == 2)
	{
		SDL_Surface *enemy_2 = IMG_Load("image/tower_2.png");
		SDL_Rect frame2 = { 0 * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK };

		image = enemy_2;
		current_frame = frame2;
	}
	else if (type_tower == 3)
	{
		SDL_Surface *enemy_3 = IMG_Load("image/tower_3.png");
		SDL_Rect frame3 = { 0 * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK };

		image = enemy_3;
		current_frame = frame3;
	}

	position = pos;
}


Tower::~Tower()
{}

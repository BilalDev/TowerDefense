#include "Tower.h"


Tower::Tower()
{}


Tower::Tower(int type_tower, SDL_Rect pos) : type(type_tower), position(pos)
{
	if (type_tower == 1)
		image = IMG_Load("image/tower_1.png");
	else if (type_tower == 2)
		image = IMG_Load("image/tower_2.png");
	else if (type_tower == 3)
		image = IMG_Load("image/tower_3.png");

	current_frame = { 0 * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK };
}


Tower::~Tower()
{}


int Tower::getType()
{
	return this->type;
}


SDL_Rect Tower::getFrame()
{
	return this->current_frame;
}


SDL_Rect Tower::getPosition()
{
	return this->position;
}


SDL_Surface* Tower::getImage()
{
	return this->image;
}

#include "Tower.h"

using namespace std;

Tower::Tower()
{}


Tower::Tower(int type_tower, SDL_Rect pos) : type(type_tower), position(pos)
{
	if (type_tower == 1)
	{
		image = IMG_Load("image/tower_1.png");
		bullet = IMG_Load("image/tower_1_bullet.png");
	}
	else if (type_tower == 2)
	{
		image = IMG_Load("image/tower_2.png");
		bullet = IMG_Load("image/tower_2_bullet.png");
	}
	else if (type_tower == 3)
	{
		image = IMG_Load("image/tower_3.png");
		bullet = IMG_Load("image/tower_3_bullet.png");
	}

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


SDL_Rect Tower::getPositionBullet()
{
	return this->positionBullet;
}


SDL_Surface* Tower::getImage()
{
	return this->image;
}


SDL_Surface* Tower::getBullet()
{
	return this->bullet;
}


void Tower::fire()
{
	if (positionBullet.y == 0)
	{
		positionBullet.x = position.x + (SIZE_BLOCK / 2 - bullet->w / 2);
		positionBullet.y = position.y + (SIZE_BLOCK / 2);
	}

	else
	{
		positionBullet = getPositionBullet();
		positionBullet.y += 5;
	}
}


void Tower::collision(vector<Enemy> *enemies)
{
	if (positionBullet.y >= BOARD_H || positionBullet.y <= 0)
	{
		positionBullet.y = position.y + (SIZE_BLOCK / 2);
	}
	else
	{
		for (vector<Enemy>::iterator &enemy = enemies->begin(); enemy != enemies->end(); ++enemy)
		{
			if ((positionBullet.y >= enemy->getPosition().y) && (positionBullet.y <= enemy->getPosition().y + SIZE_BLOCK)
				&& (positionBullet.y + bullet->h >= enemy->getPosition().y) && (positionBullet.y + bullet->h <= enemy->getPosition().y + SIZE_BLOCK)
				&& (positionBullet.x >= enemy->getPosition().x) && (positionBullet.x <= enemy->getPosition().x + SIZE_BLOCK)
				&& (positionBullet.x + bullet->w >= enemy->getPosition().x) && (positionBullet.x + bullet->w <= enemy->getPosition().x + SIZE_BLOCK))
			{
				positionBullet.y = position.y + (SIZE_BLOCK / 2);
				enemy->setLife(enemy->getLife() - 1);
			}
		}
	}
}
#include "Tower.h"

using namespace std;

Tower::Tower()
{}


Tower::Tower(int type_tower, SDL_Rect pos) : type(type_tower), position(pos)
{
	if (type_tower == 1)
	{
		image	= IMG_Load("image/tower_1.png");
		bullet	= IMG_Load("image/tower_1_bullet.png");
		price	= 1000;
	}
	else if (type_tower == 2)
	{
		image	= IMG_Load("image/tower_2.png");
		bullet	= IMG_Load("image/tower_2_bullet.png");
		price	= 500;
	}
	else if (type_tower == 3)
	{
		image	= IMG_Load("image/tower_3.png");
		bullet	= IMG_Load("image/tower_3_bullet.png");
		price	= 100;
	}

	current_frame = { 0 * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK };
}


Tower::~Tower()
{}


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


int Tower::getType()
{
	return this->type;
}


int Tower::getPrice()
{
	return this->price;
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
		int leftBullet, leftEnemy;
		int rightBullet, rightEnemy;
		int topBullet, topEnemy;
		int bottomBullet, bottomEnemy;

		leftBullet = positionBullet.x;
		rightBullet = positionBullet.x + bullet->w;
		topBullet = positionBullet.y;
		bottomBullet = positionBullet.y + bullet->h;

		for (vector<Enemy>::iterator &enemy = enemies->begin(); enemy != enemies->end(); ++enemy)
		{
			bool collided = true;
			leftEnemy = enemy->getPosition().x;
			rightEnemy = enemy->getPosition().x + SIZE_BLOCK;
			topEnemy = enemy->getPosition().y;
			bottomEnemy = enemy->getPosition().y + SIZE_BLOCK;

			if (bottomBullet <= topEnemy)
				collided = false;
			if (topBullet >= bottomEnemy)
				collided = false;
			if (rightBullet <= leftEnemy)
				collided = false;
			if (leftBullet >= rightEnemy)
				collided = false;

			if (collided)
			{
				positionBullet.y = position.y + (SIZE_BLOCK / 2);
				enemy->setLife(enemy->getLife() - 1);
			}
		}
	}
}
#include "Enemy.h"


Enemy::Enemy()
{}


Enemy::Enemy(int type_enemy, int time) : type(type_enemy), animation_time(time)
{
	SDL_Rect pos = { 0, 105 };
	
	if (type_enemy == 1)
	{
		image		= IMG_Load("image/enemy_1.png");
		velocity	= 1;
		points		= 20;
		life		= 3;
	}
	else if (type_enemy == 2)
	{
		image		= IMG_Load("image/enemy_2.png");
		velocity	= 2;
		points		= 50;
		life		= 5;
	}
	else if (type_enemy == 3)
	{
		image		= IMG_Load("image/enemy_3.png");
		velocity	= 3;
		points		= 100;
		life		= 7;
	}

	current_frame = { RIGHT * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK };
	position = pos;
}


Enemy::~Enemy()
{
}


SDL_Rect Enemy::getFrame()
{
	return this->current_frame;
}


SDL_Rect Enemy::getPosition()
{
	return this->position;
}


SDL_Surface* Enemy::getImage()
{
	return this->image;
}


int Enemy::getType()
{
	return this->type;
}


int Enemy::getLife()
{
	return this->life;
}


void Enemy::setLife(int new_life)
{
	this->life = new_life;
}


int Enemy::getVelocity()
{
	return this->velocity;
}


int Enemy::getPoints()
{
	return this->points;
}


void Enemy::move(int time)
{
	if (life > 0)
	{
		if (position.x >= 0 && position.x <= 190 && position.y <= 105)
		{
			position.x += velocity;
			animate(RIGHT, time);
		}
		else if (position.x >= 190 && position.x <= 250 && position.y <= 520)
		{
			position.y += velocity;
			animate(DOWN, time);
		}
		else if (position.x >= 190 && position.x <= 380 && position.y >= 520)
		{
			position.x += velocity;
			animate(RIGHT, time);
		}
		else if (position.x >= 380 && position.x <= 565 && position.y >= 105)
		{
			position.y -= velocity;
			animate(UP, time);
		}
		else if (position.x >= 380 && position.x <= 565 && position.y <= 105)
		{
			position.x += velocity;
			animate(RIGHT, time);
		}
		else if (position.x >= 565 && position.x <= 640 && position.y <= 300)
		{
			position.y += velocity;
			animate(DOWN, time);
		}
		else if (position.x >= 566 && position.x <= 680 && position.y >= 300)
		{
			position.x += velocity;
			animate(RIGHT, time);
		}
		else if (position.x >= 680 && position.x <= 760 && position.y >= 10 && position.y <= 305)
		{
			position.y -= velocity;
			animate(UP, time);
		}
		else if (position.x >= 680 && position.x <= 850 && position.y <= 10)
		{
			position.x += velocity;
			animate(RIGHT, time);
		}
		else if (position.x >= 850 && position.x <= 900 && position.y <= 440)
		{
			position.y += velocity;
			animate(DOWN, time);
		}
		else if (position.x >= 720 && position.x <= 900 && position.y >= 440)
		{
			position.x -= velocity;
			animate(LEFT, time);
		}
		else if (position.x >= 700 && position.x <= 800 && position.y <= 620)
		{
			position.y += velocity;
			animate(DOWN, time);
		}
	}
	else if (life == -1)
	{
		current_frame.x += SIZE_BLOCK;
		if (current_frame.x == 5 * SIZE_BLOCK)
			life = -2;
	}
}


void Enemy::change_direction(int direction)
{
	if (type == 1 || type == 3)
	{
		switch (direction)
		{
		case UP:
			current_frame.y = 0;
			break;
		case RIGHT:
			current_frame.y = SIZE_BLOCK;
			break;
		case DOWN:
			current_frame.y = 2 * SIZE_BLOCK;
			break;
		case LEFT:
			current_frame.y = 3 * SIZE_BLOCK;
			break;
		}
	}
	if (type == 2)
	{
		switch (direction)
		{
		case UP:
			current_frame.x = 0;
			break;
		case RIGHT:
			current_frame.x = SIZE_BLOCK;
			break;
		case DOWN:
			current_frame.x = 2 * SIZE_BLOCK;
			break;
		case LEFT:
			current_frame.x = 3 * SIZE_BLOCK;
			break;
		}
	}
}


void Enemy::animate(int direction, int time)
{
	change_direction(direction);

	if (type == 1 && (time >= animation_time))
	{
		if (current_frame.x == 2 * SIZE_BLOCK)
			current_frame.x = 0;
		else
			current_frame.x += SIZE_BLOCK;

		animation_time += 200;
	}
	if (type == 3 && (time >= animation_time))
	{
		if (current_frame.x == SIZE_BLOCK)
			current_frame.x = 0;
		else
			current_frame.x += SIZE_BLOCK;

		animation_time += 200;
	}
}


void Enemy::destruction()
{
	if (life == 0)
	{
		image			= IMG_Load("image/explosion.png");
		current_frame.x = -SIZE_BLOCK;
		current_frame.y = 0;
		current_frame.h = SIZE_BLOCK;
		current_frame.w = SIZE_BLOCK;
		life			= -1;
	}
}

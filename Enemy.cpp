#include "Enemy.h"


Enemy::Enemy()
{}


Enemy::Enemy(int type_enemy) : life(3), type(type_enemy)
{
	SDL_Rect pos = { 0, 105 };
	
	if (type_enemy == 1)
	{
		SDL_Surface *enemy_1 = IMG_Load("image/enemy_1.png");
		SDL_Rect frame1 = { RIGHT * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK };
		
		image = enemy_1;
		current_frame = frame1;
		velocity = 1;
	}
	else if (type_enemy == 2)
	{
		SDL_Surface *enemy_2 = IMG_Load("image/enemy_2.png");
		SDL_Rect frame2 = { RIGHT * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK };
		
		image = enemy_2;
		current_frame = frame2;
		velocity = 2;
	}
	else if (type_enemy == 3)
	{
		SDL_Surface *enemy_3 = IMG_Load("image/enemy_3.png");
		SDL_Rect frame3 = { RIGHT * SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK, SIZE_BLOCK };
		
		image = enemy_3;
		current_frame = frame3;
		velocity = 3;
	}

	position = pos;
}


Enemy::Enemy(SDL_Surface *img, SDL_Rect *frame, SDL_Rect *pos, int veloc, int type_enemy) : life(3), velocity(veloc), type(type_enemy)
{
	image = img;
	current_frame = *frame;
	position = *pos;
}


Enemy::~Enemy()
{
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


int Enemy::getType()
{
	return this->type;
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


void Enemy::move()
{
	if (life > 0)
	{
		if (position.x >= 0 && position.x <= 190 && position.y <= 105)
		{
			position.x += velocity;
			animate(RIGHT);
		}
		else if (position.x >= 190 && position.x <= 250 && position.y <= 520)
		{
			position.y += velocity;
			animate(DOWN);
		}
		else if (position.x >= 190 && position.x <= 380 && position.y >= 520)
		{
			position.x += velocity;
			animate(RIGHT);
		}
		else if (position.x >= 380 && position.x <= 565 && position.y >= 105)
		{
			position.y -= velocity;
			animate(UP);
		}
		else if (position.x >= 380 && position.x <= 565 && position.y <= 105)
		{
			position.x += velocity;
			animate(RIGHT);
		}
		else if (position.x >= 565 && position.x <= 640 && position.y <= 300)
		{
			position.y += velocity;
			animate(DOWN);
		}
		else if (position.x >= 566 && position.x <= 680 && position.y >= 300)
		{
			position.x += velocity;
			animate(RIGHT);
		}
		else if (position.x >= 680 && position.x <= 760 && position.y >= 10 && position.y <= 305)
		{
			position.y -= velocity;
			animate(UP);
		}
		else if (position.x >= 680 && position.x <= 850 && position.y <= 10)
		{
			position.x += velocity;
			animate(RIGHT);
		}
		else if (position.x >= 850 && position.x <= 900 && position.y <= 440)
		{
			position.y += velocity;
			animate(DOWN);
		}
		else if (position.x >= 720 && position.x <= 900 && position.y >= 440)
		{
			position.x -= velocity;
			animate(LEFT);
		}
		else if (position.x >= 700 && position.x <= 800 && position.y <= 620)
		{
			position.y += velocity;
			animate(DOWN);
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


void Enemy::animate(int direction)
{
	change_direction(direction);

	if (type == 1)
	{
		if (current_frame.x == 2 * SIZE_BLOCK)
			current_frame.x = 0;
		else
			current_frame.x += SIZE_BLOCK;
	}
	if (type == 3)
	{
		if (current_frame.x == SIZE_BLOCK)
			current_frame.x = 0;
		else
			current_frame.x += SIZE_BLOCK;
	}
}


void Enemy::destruction()
{
	if (life == 0)
	{
		image = NULL;
		image = IMG_Load("image/explosion.png");
		current_frame.x = -SIZE_BLOCK;
		current_frame.y = 0;
		current_frame.h = SIZE_BLOCK;
		current_frame.w = SIZE_BLOCK;
		life = -1;
	}
}

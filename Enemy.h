#pragma once

#define SIZE_BLOCK	59

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

enum DirectionEnemy { UP, RIGHT, DOWN, LEFT };

#include <iostream>
#include <string>

class Enemy
{
public:
	// CONSTRUCTOR DESTRUCTOR
	Enemy();
	Enemy(int type_enemy);
	Enemy(SDL_Surface *img, SDL_Rect *frame, SDL_Rect *pos, int veloc, int type_enemy);
	~Enemy();
	// METHOD
	void move();
	void change_direction(int direction);
	void animate(int direction);
	void destruction();
	// GETTER SETTER
	int			getLife();
	void		setLife(int new_life);
	int			getVelocity();
	int			getType();
	SDL_Rect	getFrame();
	SDL_Rect	getPosition();
	SDL_Surface	*getImage();


private:
	SDL_Rect	current_frame;
	SDL_Rect	position;
	SDL_Surface	*image;
	int			type;
	int			life;
	int			velocity;
};
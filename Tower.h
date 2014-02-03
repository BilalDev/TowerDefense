#pragma once

#define SIZE_BLOCK	59

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <string>

class Tower
{
public:
	// CONSTRUCTOR DESTRUCTOR
	Tower();
	Tower(int type_tower);
	Tower(SDL_Surface *img, SDL_Rect *frame, SDL_Rect *pos, int type_tower);
	~Tower();
private:
	SDL_Rect	current_frame;
	SDL_Rect	position;
	SDL_Surface	*image;
	int			type;
};
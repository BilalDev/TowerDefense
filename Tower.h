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
	Tower(int type_enemy);
	Tower(SDL_Surface *img, SDL_Rect *frame, SDL_Rect *pos, int veloc, int type_enemy);
	~Tower();
private:

};
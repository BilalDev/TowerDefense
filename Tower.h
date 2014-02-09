#ifndef TOWER_H
#define TOWER_H

	#include "header.h"
	#include "Enemy.h"

	class Tower
	{
	public:
		// CTOR DTOR
		Tower();
		Tower(int type_tower, SDL_Rect pos);
		Tower(SDL_Surface *img, SDL_Rect *frame, SDL_Rect *pos, int type_tower);
		~Tower();
		// METHOD
		void		fire();
		void		collision(std::vector<Enemy> *enemies);
		// GETTER SETTER
		int			getType();
		SDL_Rect	getFrame();
		SDL_Rect	getPosition();
		SDL_Surface	*getImage();
		SDL_Rect	getPositionBullet();
		SDL_Surface	*getBullet();
	
	private:
		SDL_Rect	current_frame;
		SDL_Rect	position;
		SDL_Surface	*image;
		SDL_Rect	positionBullet;
		SDL_Surface *bullet;
		int			type;
	};

#endif /* !TOWER_H */
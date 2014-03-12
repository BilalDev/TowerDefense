#ifndef TOWER_H
#define TOWER_H

	#include "header.h"
	#include "Enemy.h"

	class Tower
	{
	public:
		// CTOR DTOR
		Tower();
		Tower(int type_tower, SDL_Rect pos, int time);
		~Tower();
		// METHOD
		void		fire(int time);
		void		collision(std::vector<Enemy> *enemies);
		// GETTER SETTER
		SDL_Rect	getFrame();
		SDL_Rect	getPosition();
		SDL_Surface	*getImage();
		SDL_Rect	getPositionBullet();
		SDL_Surface	*getBullet();
		int			getType();
		int			getPrice();
	
	private:
		SDL_Rect	current_frame;
		SDL_Rect	position;
		SDL_Surface	*image;
		SDL_Rect	positionBullet;
		SDL_Surface *bullet;
		int			type;
		int			price;
		int			animation_time;
	};

#endif /* !TOWER_H */
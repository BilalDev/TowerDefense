#ifndef ENEMY_H
#define ENEMY_H

	#include "header.h"

	enum DirectionEnemy { UP, RIGHT, DOWN, LEFT };

	class Enemy
	{
	public:
		// CTOR DTOR
		Enemy();
		Enemy(int type_enemy);
		~Enemy();
		// METHOD
		void move();
		void change_direction(int direction);
		void animate(int direction);
		void destruction();
		// GETTER SETTER
		SDL_Rect	getFrame();
		SDL_Rect	getPosition();
		SDL_Surface	*getImage();
		int			getType();
		int			getLife();
		void		setLife(int new_life);
		int			getVelocity();
		int			getPoints();


	private:
		SDL_Rect	current_frame;
		SDL_Rect	position;
		SDL_Surface	*image;
		int			type;
		int			life;
		int			velocity;
		int			points;
	};

#endif /* !ENEMY_H */
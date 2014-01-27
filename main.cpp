#include "header.h"

using namespace std;

int main(int argc, char** argv)
{
	// WORLD VARIABLES
	SDL_Surface *screen = NULL, *background = NULL, *menu = NULL;
	SDL_Rect positionMenu;
	SDL_Event event;
	bool play = true;
	
	// FONT
	TTF_Font    *font40 = NULL, *font100 = NULL;
	SDL_Color   white = { 255, 255, 255 };
	int			valuePoints = 0, valueLife = 5;
	string		textPoints, textLife;
	SDL_Surface	*points = NULL, *life = NULL, *gameover = NULL;
	SDL_Rect	positionPoints, positionLife, positionGO;


	// ENEMIES
	vector<Enemy> enemies;

	// CONTROL FPS
	Uint32 start;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur lors du chargement de la SDL %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	// Init screen
	screen = SDL_SetVideoMode(944, 767, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Tower Defense", NULL);

	// Init game, font, menu
	background = IMG_Load("image/background.png");
	menu = IMG_Load("image/menu.png");
	positionMenu.x = 0;
	positionMenu.y = 649;
	
	TTF_Init();
	font40 = TTF_OpenFont("font/font.ttf", 40);
	font100 = TTF_OpenFont("font/font.ttf", 100);
	textPoints = "POINTS : 0";
	points = TTF_RenderText_Blended(font40, textPoints.c_str(), white);
	positionPoints.x = 700;
	positionPoints.y = positionMenu.y + 10;

	textLife = "LIFE : 5";
	life = TTF_RenderText_Blended(font40, textLife.c_str(), white);
	positionLife.x = 700;
	positionLife.y = positionPoints.y + 50;

	gameover = TTF_RenderText_Blended(font100, "GAME OVER", white);
	positionGO.x = 949 / 2 - (gameover->w / 2);
	positionGO.y = 767 / 2 - (gameover->h / 2);



	while (play)
	{
		start = SDL_GetTicks();

		// INPUT PLAYER
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				play = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					play = false;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}



		// LOGIC
		if (valueLife > 0)
		{
			if (SDL_GetTicks() % 100 == 0)
			{
				// RAND [1 ; 3];
				int random = std::rand() % (4 - 1) + 1;

				Enemy e = Enemy(random);
				enemies.push_back(e);
			}
			for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
			{
				// if no more life, stop position & start animation of destruction
				if ((*it).getLife() == 0)
					(*it).destruction();

				(*it).move();

				// if destruction finished, free then delete from vector
				if ((*it).getLife() == -2)
				{
					SDL_FreeSurface((*it).getImage());
					enemies.erase(it);
				}
				// if enemy OOTB, free then delete from vector and take off a life
				if ((*it).getPosition().y >= 620)
				{
					SDL_FreeSurface((*it).getImage());
					enemies.erase(it);
					textLife = "LIFE : " + to_string(--valueLife);
					life = TTF_RenderText_Blended(font40, textLife.c_str(), white);
				}
			}
		}



		// RENDER
		SDL_BlitSurface(background, NULL, screen, NULL);

		for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
			SDL_BlitSurface((*it).getImage(), &(*it).getFrame(), screen, &(*it).getPosition());

		SDL_BlitSurface(menu, NULL, screen, &positionMenu);
		SDL_BlitSurface(points, NULL, screen, &positionPoints);
		SDL_BlitSurface(life, NULL, screen, &positionLife);

		if (valueLife <= 0)
			SDL_BlitSurface(gameover, NULL, screen, &positionGO);

		SDL_Flip(screen);

		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}

	// FREE
	for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		SDL_FreeSurface((*it).getImage());

	SDL_FreeSurface(background);
	SDL_FreeSurface(gameover);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(life);

	TTF_CloseFont(font40);
	TTF_CloseFont(font100);
	
	TTF_Quit();
	SDL_Quit();

	return (EXIT_SUCCESS);
}
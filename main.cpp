#include "header.h"

using namespace std;

int main(int argc, char** argv)
{
	// WORLD VARIABLES
	SDL_Surface *screen = NULL, *background = NULL, *menu = NULL, *towersImg = NULL;
	SDL_Rect positionMenu, positionTowers;
	SDL_Event event;
	bool play = true;
	
	// FONT
	TTF_Font    *font40 = NULL, *font100 = NULL;
	SDL_Color   white = { 255, 255, 255 };
	SDL_Color   yellow = { 241, 196, 15 };

	// MENU
	int			valuePoints = 0, valueLife = 5;
	string		textPoints, textLife;
	SDL_Surface	*points = NULL, *life = NULL, *gameover = NULL;
	SDL_Rect	positionPoints, positionLife, positionGO;
	int			sizeTowers;

	// ENEMIES
	vector<Enemy> enemies;
	
	// TOWERS
	vector<Tower>	towers;
	int				typeTower;

	// TOWER SELECTED
	SDL_Surface *towerSelected = NULL;
	SDL_Rect	positionTowerSelected, frameTowerSelected;
	bool		isTowerSelected, isTowerPlaced;

	// CONTROL FPS
	Uint32 start;

	// DEBUG
	// MOUSE INFORMATION
	SDL_Surface *mouse = NULL;
	SDL_Rect	positionMouse;
	string		textMouse;

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
	positionMenu = { 0, 767 - menu->h };
	towersImg = IMG_Load("image/towers.png");
	positionTowers = { 0, 767 - towersImg->h };
	sizeTowers = towersImg->w / 3;
	
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


	towerSelected = IMG_Load("image/mini-towers.png");
	positionTowerSelected = { 0, 0 };
	frameTowerSelected = { 0, 0, SIZE_BLOCK, SIZE_BLOCK };
	isTowerSelected = isTowerPlaced = false;

	// DEBUG
	// INIT MOUSE INFORMATION
	positionMouse = { 0, 0 };
	textMouse = "x : 0 y : 0";
	mouse = TTF_RenderText_Blended(font40, textMouse.c_str(), yellow);




	// MAIN GAME LOOP
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
			case SDL_MOUSEMOTION:
				// DEBUG
				textMouse = "x : " + to_string(event.motion.x) + " y : " + to_string(event.motion.y);
				mouse = TTF_RenderText_Blended(font40, textMouse.c_str(), yellow);
				
				if (isTowerSelected)
				{
					positionTowerSelected.x = event.motion.x - (SIZE_BLOCK / 2);
					positionTowerSelected.y = event.motion.y - (SIZE_BLOCK / 2);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				// Handle selection of tower type
				if (!isTowerSelected)
				{
					if (event.motion.y >= positionTowers.y && event.motion.x <= (3 * sizeTowers))
					{
						if (event.motion.x >= 0 && event.motion.x < sizeTowers)
						{
							frameTowerSelected.x = 0 * SIZE_BLOCK;
							typeTower = 1;
						}
						else if (event.motion.x >= sizeTowers && event.motion.x < 2 * sizeTowers)
						{
							frameTowerSelected.x = 1 * SIZE_BLOCK;
							typeTower = 2;
						}
						else if (event.motion.x >= 2 * sizeTowers && event.motion.x < 3 * sizeTowers)
						{
							frameTowerSelected.x = 2 * SIZE_BLOCK;
							typeTower = 3;
						}
						positionTowerSelected.x = event.motion.x - (SIZE_BLOCK / 2);
						positionTowerSelected.y = event.motion.y - (SIZE_BLOCK / 2);
						isTowerSelected = true;
					}
				}
				else if (isTowerSelected)
				{
					isTowerSelected = false;
					Tower t = Tower(typeTower, positionTowerSelected);
					towers.push_back(t);
				}
				break;
			default:
				break;
			}
		}



		// LOGIC
		if (valueLife > 0)
		{
			// TOWER'S LOGIC

			// ENEMY'S LOGIC
			if (SDL_GetTicks() % 300 == 0)
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
		for (vector<Tower>::iterator it = towers.begin(); it != towers.end(); ++it)
			SDL_BlitSurface((*it).getImage(), &(*it).getFrame(), screen, &(*it).getPosition());
		// menu
		SDL_BlitSurface(menu, NULL, screen, &positionMenu);
		SDL_BlitSurface(towersImg, NULL, screen, &positionTowers);
		SDL_BlitSurface(points, NULL, screen, &positionPoints);
		SDL_BlitSurface(life, NULL, screen, &positionLife);
		if (isTowerSelected)
			SDL_BlitSurface(towerSelected, &frameTowerSelected, screen, &positionTowerSelected);
		if (valueLife <= 0)
			SDL_BlitSurface(gameover, NULL, screen, &positionGO);
		// DEBUG
		SDL_BlitSurface(mouse, NULL, screen, &positionMouse);

		SDL_Flip(screen);


		if (1000 / FPS > SDL_GetTicks() - start)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
	}

	printf("%d", towers.size());

	// FREE
	for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
		SDL_FreeSurface((*it).getImage());
	for (vector<Tower>::iterator it = towers.begin(); it != towers.end(); ++it)
		SDL_FreeSurface((*it).getImage());

	SDL_FreeSurface(background);
	SDL_FreeSurface(gameover);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(towersImg);
	SDL_FreeSurface(life);

	TTF_CloseFont(font40);
	TTF_CloseFont(font100);
	
	TTF_Quit();
	SDL_Quit();

	return (EXIT_SUCCESS);
}
#include "header.h"
#include "Enemy.h"
#include "Tower.h"
#include "Timer.h"

using namespace std;

int main(int argc, char** argv)
{
	// WORLD VARIABLES
	SDL_Surface *screen = NULL, *background = NULL, *menu = NULL, *towersImg = NULL;
	SDL_Rect positionMenu, positionTowers;
	SDL_Event event;
	bool play = true;
	
	// FONT
	TTF_Font    *font20 = NULL, *font100 = NULL;
	SDL_Color   white = { 255, 255, 255 };
	SDL_Color   yellow = { 241, 196, 15 };

	// MENU
	int			valuePoints = 0, valueLife = 15, valueMoney = 100;
	string		textPoints, textLife, textMoney;
	SDL_Surface	*points = NULL, *life = NULL, *money = NULL, *gameover = NULL;
	SDL_Rect	positionPoints, positionLife, positionMoney, positionGO;
	int			sizeTowers;

	// ENEMIES
	vector<Enemy> enemies;
	
	// TOWERS
	vector<Tower>	towers;
	int				typeTower;

	// TOWER SELECTED
	SDL_Surface *towerSelected = NULL;
	SDL_Rect	positionTowerSelected, frameTowerSelected;
	bool		isTowerSelected, hasEnoughMoney;

	// CONTROL TIME
	Uint32 start;
	Timer timer;
	int spotTime;

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
	screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Tower Defense", NULL);

	// Init game, font, menu
	background = IMG_Load("image/background.png");
	menu = IMG_Load("image/menu.png");
	positionMenu = { 0, WINDOW_H - menu->h };
	towersImg = IMG_Load("image/towers.png");
	positionTowers = { 0, WINDOW_H - towersImg->h };
	sizeTowers = towersImg->w / 3;
	
	TTF_Init();
	font20 = TTF_OpenFont("font/font.ttf", 20);
	font100 = TTF_OpenFont("font/font.ttf", 100);
	textPoints = "POINTS : 0";
	points = TTF_RenderText_Blended(font20, textPoints.c_str(), white);
	positionPoints.x = 700;
	positionPoints.y = positionMenu.y + 10;

	textLife = "LIFE : " + to_string(valueLife);
	life = TTF_RenderText_Blended(font20, textLife.c_str(), white);
	positionLife.x = 700;
	positionLife.y = positionPoints.y + 35;

	textMoney = "MONEY : " + to_string(valueMoney) + "$";
	money = TTF_RenderText_Blended(font20, textMoney.c_str(), white);
	positionMoney.x = 700;
	positionMoney.y = positionPoints.y + 70;

	gameover = TTF_RenderText_Blended(font100, "GAME OVER", white);
	positionGO.x = WINDOW_W / 2 - (gameover->w / 2);
	positionGO.y = WINDOW_H / 2 - (gameover->h / 2);


	towerSelected = IMG_Load("image/mini-towers.png");
	positionTowerSelected = { 0, 0 };
	frameTowerSelected = { 0, 0, SIZE_BLOCK, SIZE_BLOCK };
	isTowerSelected = hasEnoughMoney = false;

	// DEBUG
	// INIT MOUSE INFORMATION
	positionMouse = { 0, 0 };
	textMouse = "x : 0 y : 0";
	mouse = TTF_RenderText_Blended(font20, textMouse.c_str(), yellow);



	timer.start();
	spotTime = timer.getTicks() + 1000;
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
				mouse = TTF_RenderText_Blended(font20, textMouse.c_str(), yellow);
				
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
						// ENEMY TYPE 1
						if (event.motion.x >= 0 && event.motion.x < sizeTowers)
						{
							if (valueMoney >= 1000)
							{
								frameTowerSelected.x = 0 * SIZE_BLOCK;
								typeTower = 1;
								hasEnoughMoney = true;
								isTowerSelected = true;
								valueMoney -= 1000;
								textMoney = "MONEY : " + to_string(valueMoney) + "$";
								money = TTF_RenderText_Blended(font20, textMoney.c_str(), white);
							}
							else
								hasEnoughMoney = false;
						}
						// ENEMY TYPE 2
						else if (event.motion.x >= sizeTowers && event.motion.x < 2 * sizeTowers)
						{
							if (valueMoney >= 500)
							{
								frameTowerSelected.x = 1 * SIZE_BLOCK;
								typeTower = 2;
								hasEnoughMoney = true;
								isTowerSelected = true;
								valueMoney -= 500;
								textMoney = "MONEY : " + to_string(valueMoney) + "$";
								money = TTF_RenderText_Blended(font20, textMoney.c_str(), white);
							}
							else
								hasEnoughMoney = false;
						}
						// ENEMY TYPE 3
						else if (event.motion.x >= 2 * sizeTowers && event.motion.x < 3 * sizeTowers)
						{
							if (valueMoney >= 100)
							{
								frameTowerSelected.x = 2 * SIZE_BLOCK;
								typeTower = 3;
								hasEnoughMoney = true;
								isTowerSelected = true;
								valueMoney -= 100;
								textMoney = "MONEY : " + to_string(valueMoney) + "$";
								money = TTF_RenderText_Blended(font20, textMoney.c_str(), white);
							}
							else
								hasEnoughMoney = false;
						}
						positionTowerSelected.x = event.motion.x - (SIZE_BLOCK / 2);
						positionTowerSelected.y = event.motion.y - (SIZE_BLOCK / 2);
					}
				}
				else if (isTowerSelected && hasEnoughMoney)
				{
					isTowerSelected = false;
					Tower t = Tower(typeTower, positionTowerSelected, timer.getTicks());
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
			for (vector<Tower>::iterator tower = towers.begin(); tower != towers.end(); ++tower)
			{
				(*tower).fire(timer.getTicks());
				(*tower).collision(&enemies);
			}

			// ENEMY'S LOGIC
			if (timer.getTicks() >= spotTime)
			{
				// Enemy spots every 1s
				spotTime = timer.getTicks() + 2000;
				
				// RAND [1 ; 3];
				int randType = std::rand() % (4 - 1) + 1;
				Enemy e = Enemy(randType, timer.getTicks());
				enemies.push_back(e);
			}
			for (vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
			{
				// if no more life, stop position & start animation of destruction
				if ((*enemy).getLife() == 0)
				{
					(*enemy).destruction();
					valuePoints += (*enemy).getPoints();
					textPoints = "POINTS : " + to_string(valuePoints);
					points = TTF_RenderText_Blended(font20, textPoints.c_str(), white);
				}

				(*enemy).move(timer.getTicks());

				// if destruction finished, free then delete from vector and add money$$$$
				if ((*enemy).getLife() == -2)
				{
					// FREE SURFACE
					SDL_FreeSurface((*enemy).getImage());
					// ADD MONEY
					valueMoney += (*enemy).getPoints();
					textMoney = "MONEY : " + to_string(valueMoney) + "$";
					money = TTF_RenderText_Blended(font20, textMoney.c_str(), white);
					// DELETE FROM VECTOR
					enemies.erase(enemy);
					break;
				}
				// if enemy OOTB, free then delete from vector and take off a life
				if ((*enemy).getPosition().y >= 620)
				{
					SDL_FreeSurface((*enemy).getImage());
					enemies.erase(enemy);
					textLife = "LIFE : " + to_string(--valueLife);
					life = TTF_RenderText_Blended(font20, textLife.c_str(), white);
				}
			}
		}



		// RENDER
		SDL_BlitSurface(background, NULL, screen, NULL);
		for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it)
			SDL_BlitSurface((*it).getImage(), &(*it).getFrame(), screen, &(*it).getPosition());
		for (vector<Tower>::iterator it = towers.begin(); it != towers.end(); ++it)
		{
			SDL_BlitSurface((*it).getImage(), &(*it).getFrame(), screen, &(*it).getPosition());
			SDL_BlitSurface((*it).getBullet(), NULL, screen, &(*it).getPositionBullet());
		}
		// menu
		SDL_BlitSurface(menu, NULL, screen, &positionMenu);
		SDL_BlitSurface(towersImg, NULL, screen, &positionTowers);
		SDL_BlitSurface(points, NULL, screen, &positionPoints);
		SDL_BlitSurface(life, NULL, screen, &positionLife);
		SDL_BlitSurface(money, NULL, screen, &positionMoney);
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

	// FREE
	for (vector<Enemy>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
		SDL_FreeSurface((*enemy).getImage());
	for (vector<Tower>::iterator tower = towers.begin(); tower != towers.end(); ++tower)
		SDL_FreeSurface((*tower).getImage());

	SDL_FreeSurface(background);
	SDL_FreeSurface(gameover);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(towersImg);
	SDL_FreeSurface(mouse);
	SDL_FreeSurface(towerSelected);
	SDL_FreeSurface(life);
	SDL_FreeSurface(money);
	SDL_FreeSurface(points);

	TTF_CloseFont(font20);
	TTF_CloseFont(font100);
	
	TTF_Quit();
	SDL_Quit();

	return (EXIT_SUCCESS);
}
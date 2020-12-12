#include "demo.h"

/**
 * draw_stuff - draws some simple stuff in the instance
 *
 * @instance: SDL instance
 *
 * Return: Void
 */
void draw_stuff(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(instance.renderer, 10, 10, 1200, 700);
}



/**
 * poll_events - check for Keyboard events from the user
 *
 * @theta : theta angle
 * @altp : altitude percent
 * @zoom : zoom on the surface
 *
 * Return: 1 if quit
 */

int poll_events(int *theta, int *altp, int *zoom)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;

			if (key.keysym.scancode == 0x29)
				return (1);
			if (key.keysym.sym == SDLK_LEFT)
				*theta += 2;
			if (key.keysym.sym == SDLK_RIGHT)
				*theta -= 2;
			if (key.keysym.sym == SDLK_UP)
				*altp += 2;
			if (key.keysym.sym == SDLK_DOWN)
				*altp -= 2;
			if (key.keysym.sym == SDLK_KP_PLUS)
				*zoom += 2;
			if (key.keysym.sym == SDLK_KP_MINUS)
				*zoom -= 2;

			break;
		}
	}
}


/**
 * main - main program
 *
 * @ac : number of arguments
 * @av : the tab with the arguments
 *
 * Return: 0 on Sucess, 1 on Error
 */

int main(int ac, char **av)
{
	int **alt;
	int row = 0, col = 0, zoom, theta = 0, altp = 100;
	Point3D **g3Init, **g3Final;
	Point2D **g2Init, **g2Final;
	SDL_Instance instance;

	if (ac != 2)
	{
		printf("Usage 'terrain file'\n");
		return (1);
	}
	alt = getaltfromfile(av[1], &col, &row);
	g3Init = getGraph3D(alt, row, col, LSIZE);
	g2Init = getGraph2D(g3Init, row, col);
	zoom = getZoom2D(g2Init, row, col, MARGIN);

	g3Final = moveGraph3D(g3Init, row, col, theta, altp);
	g2Final = getGraph2D(g3Final, row, col);

	if (init_instance(&instance) != 0)
		return (1);
	while ("C is awesome")
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance.renderer);
		if (poll_events(&theta, &altp, &zoom) == 1)
			break;

		freeGraph3D(g3Final, row, col);
		freeGraph2D(g2Final, row, col);
		g3Final = moveGraph3D(g3Init, row, col, theta, altp);
		g2Final = getGraph2D(g3Final, row, col);
		draw_grid(instance, g2Final, row, col, zoom);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}

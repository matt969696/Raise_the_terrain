#ifndef _DEMO_H_
#define _DEMO_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define WINX 1260
#define WINY 720
#define INC 0.7
#define LSIZE 100
#define MARGIN 30

/**
 * struct Point3D - stoe the coordinates of a 3D point
 *
 * @X: X coordinate
 * @Y: Y coordinate
 * @Z: Z coordinate
 *
 * Description: store the a 3D point
 */

typedef struct Point3D
{
	int X;
	int Y;
	int Z;
} Point3D;

/**
 * struct Point2D - store the coordinates of a 2D point
 *
 * @WX: WX coordinate
 * @WY: WY coordinate
 *
 * Description: store the a 3D point
 */

typedef struct Point2D
{
	int WX;
	int WY;
} Point2D;


/**
 * struct SDL_Instance - store a created instance of SDL
 *
 * @window: window for the instance
 * @renderer: renderer for the instance
 *
 * Description: store the created SDL instance
 */


typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/* init.c */
int init_instance(SDL_Instance *);

/* main.c */
void draw_stuff(SDL_Instance instance);
int poll_events(int *theta, int *altp, int *zoom, int zi, int *trx, int *try);
int main(int ac, char **av);

/* grid.c */
int draw_grid(SDL_Instance ins, Point2D **g2D, int row, int col, int z, int tx, int ty);
int **getaltfromfile(char *filename, int *row, int *col);
int countcol(char *lineptr);
int *mystrtow(char *lineptr);

/* graph.c */
Point3D **getGraph3D(int **alt, int row, int col, int dist);
Point2D **getGraph2D(Point3D **g3D, int row, int col);
int getZoom2D(Point2D **g2D, int row, int col, int margin);
Point3D **moveGraph3D(Point3D **g3I, int row, int col, int theta, int altp);

/* free.c */
void freeGraph3D(Point3D **g3D, int row);
void freeGraph2D(Point2D **g2D, int row);
void freeAlt(int **g, int row);

#endif

#include "demo.h"

/**
 * freeGraph3D - frees a 3D graph
 *
 * @g3D: graph to free
 * @row : number of rows
 *
 * Return: Void
 */

void freeGraph3D(Point3D **g3D, int row)
{
	int i;

	for (i = 0; i < row; i++)
		free(g3D[i]);
	free(g3D);
}



/**
 * freeGraph2D - frees a 2D graph
 *
 * @g2D: graph to free
 * @row : number of rows
 *
 * Return: Void
 */

void freeGraph2D(Point2D **g2D, int row)
{
	int i;

	for (i = 0; i < row; i++)
		free(g2D[i]);
	free(g2D);
}


/**
 * freeAlt - frees an alt matrix
 *
 * @g: graph to free
 * @row : number of rows
 *
 * Return: Void
 */

void freeAlt(int **g, int row)
{
	int i;

	for (i = 0; i < row; i++)
		free(g[i]);
	free(g);
}

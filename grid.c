#include "demo.h"

/**
 * draw_grid - draws some simple stuff in the instance
 *
 * @instance: SDL instance
 * @g2D: graph2D
 * @row : number of rows
 * @col : number of columns
 * @zoom : zoom to apply
 * @trx : horizontal translation
 * @try : vertical translation
 *
 * Return: 0 on Success, 1 on Error
 */
int draw_grid(SDL_Instance instance, Point2D **g2D, int row, int col, int zoom, int trx, int try)
{
	int i, j, fromx, fromy, tox, toy;

	SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			fromx = trx + WINX / 2 + ((g2D[i][j].WX - WINX / 2) * zoom) / 100;
			fromy = try + WINY / 2 + ((g2D[i][j].WY - WINY / 2) * zoom) / 100;
			if (i + 1 < row)
			{
				tox = trx + WINX / 2 + ((g2D[i + 1][j].WX - WINX / 2) * zoom) / 100;
				toy = try + WINY / 2 + ((g2D[i + 1][j].WY - WINY / 2) * zoom) / 100;
				SDL_RenderDrawLine(instance.renderer, fromx, fromy, tox, toy);
			}
			if (j + 1 < col)
			{
				tox = trx + WINX / 2 + ((g2D[i][j + 1].WX - WINX / 2) * zoom) / 100;
				toy = try + WINY / 2 + ((g2D[i][j + 1].WY - WINY / 2) * zoom) / 100;
				SDL_RenderDrawLine(instance.renderer, fromx, fromy, tox, toy);
			}
		}
	}
	return (0);
}



/**
 * getaltfromfile - populates the alt matrix
 *
 * @filename: name of the file containing altitudes
 * @row : number of rows in the file
 * @col : number of columns in the file
 *
 * Return: alt matrix, NULL if error
 */

int **getaltfromfile(char *filename, int *row, int *col)
{
	FILE *fd;
	char *lineptr = NULL;
	size_t n = 0;
	int nbrow = 0, nbcol = 0, read;
	int **alt = NULL;

	if (filename == NULL)
		return (NULL);

	fd = fopen(filename, "r");
	if (fd == NULL)
	{
		printf("Can't open file %s\n", filename);
		exit(1);
	}

	while ((read = getline(&lineptr, &n, fd)) != EOF)
	{
		nbrow += 1;
		alt = realloc(alt, nbrow * sizeof(int *));
		alt[nbrow - 1] = mystrtow(lineptr);
		nbcol = countcol(lineptr);
	}
	*row = nbrow;
	*col = nbcol;
	return (alt);

	fclose(fd);
}

/**
 * countcol - read an alt line and return the number of col
 *
 * @lineptr: read line
 *
 * Return: number of alt read
 */

int countcol(char *lineptr)
{
	int nb = 0;
	char *tok;
	char *temp;

	temp = strdup(lineptr);
	tok = strtok(temp, " ");
	while (tok != NULL)
	{
		tok = strtok(NULL, " ");
		nb = nb + 1;
	}
	free(temp);
	return (nb);
}




/**
 * mystrtow - read an alt line and populates an array of alt
 *
 * @lineptr: read line
 *
 * Return: array of alt, NULL if error
 */

int *mystrtow(char *lineptr)
{
	int nb, i = 0;
	char *tok;
	char *temp;
	int *res;

	nb = countcol(lineptr);

	res = malloc(nb * sizeof(int));
	if (res == NULL)
		return (NULL);

	temp = strdup(lineptr);
	tok = strtok(temp, " ");
	while (tok != NULL)
	{
		res[i] = atoi(tok);
		tok = strtok(NULL, " ");
		i = i + 1;
	}
	free(temp);
	return (res);
}

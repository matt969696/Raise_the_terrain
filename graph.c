#include "demo.h"

/**
 * getGraph3D - populate a 3D matrix of points
 *
 * @alt: alt matrix
 * @row : number of rows
 * @col : number of col
 * @dist : distance between points
 *
 * Return: matrix of Point3D, if error NULL
 */

Point3D **getGraph3D(int **alt, int row, int col, int dist)
{
	int i, j;
	Point3D **res;
	Point3D *myline;
	Point3D point;

	res = malloc(row * sizeof(Point3D *));
	for (i = 0; i < row; i++)
	{
		myline = malloc(col * sizeof(Point3D));
		for (j = 0; j < col; j++)
		{
			point.X = i * dist - (row - 1) * (dist / 2);
			point.Y = j * dist - (col - 1) * (dist / 2);
			point.Z = alt[j][i];
			myline[j] = point;
		}
		res[i] = myline;
	}

	return (res);
}



/**
 * getGraph2D - transform a graph3D into a graph2D
 *
 * @g3D: graph3D
 * @row : number of rows
 * @col : number of col
 *
 * Return: matrix of Point2D, if error NULL
 */

Point2D **getGraph2D(Point3D **g3D, int row, int col)
{
	int i, j;
	Point2D **res;
	Point2D *myline;
	Point2D point;

	res = malloc(row * sizeof(Point2D *));
	for (i = 0; i < row; i++)
	{
		myline = malloc(col * sizeof(Point2D));
		for (j = 0; j < col; j++)
		{
			point.WX = INC * (g3D[i][j].X - g3D[i][j].Y) + WINX / 2;
			point.WY = (1 - INC) * (g3D[i][j].X + g3D[i][j].Y) - g3D[i][j].Z + WINY / 2;
			myline[j] = point;
		}
		res[i] = myline;
	}
	return (res);
}


/**
 * getZoom2D - compute the initial zoom for a graph2D
 *
 * @g2D: graph2D
 * @row : number of rows
 * @col : number of col
 * @margin : padding
 *
 * Return: initial zoom to apply in percent
 */

int getZoom2D(Point2D **g2D, int row, int col, int margin)
{
	int i, j;
	int minx, maxx, miny, maxy;
	int scale, scalefin;

	minx = WINX / 2 - 1;
	maxx = WINX / 2 + 1;
	miny = WINY / 2 - 1;
	maxy = WINY / 2 + 1;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (g2D[i][j].WX > maxx)
				maxx = g2D[i][j].WX;
			if (g2D[i][j].WX < minx)
				minx = g2D[i][j].WX;
			if (g2D[i][j].WY > maxy)
				maxy = g2D[i][j].WY;
			if (g2D[i][j].WY < miny)
				miny = g2D[i][j].WY;
		}
	}
	printf("minx %i, maxx %i, miny %i, maxy %i\n", minx, maxx, miny, maxy);
	scale = ((WINX / 2 - margin) * 100) / (WINX / 2 - minx);
	scalefin = scale;
	scale = ((WINX / 2 - margin) * 100) / (maxx - WINX / 2);
	if (scale < scalefin)
		scalefin = scale;
	scale = ((WINY / 2 - margin) * 100) / (WINY / 2 - miny);
	printf("scale is %i scalefin is %i\n", scale, scalefin);
	if (scale < scalefin)
		scalefin = scale;
	scale = ((WINY / 2 - margin) * 100) / (maxy - WINY / 2);
	if (scale < scalefin)
		scalefin = scale;
	return (scalefin);
}






/**
 * moveGraph3D - change a 3D graph by varying alt and rotation
 *
 * @g3I: init graph3D
 * @row : number of rows
 * @col : number of col
 * @theta: angle of rotation
 * @altp: altitude
 *
 * Return: matrix of Point3D, if error NULL
 */

Point3D **moveGraph3D(Point3D **g3I, int row, int col, int theta, int altp)
{
	int i, j;
	Point3D **res;
	Point3D *myline;
	Point3D point;
	float a = theta * M_PI / 180;

	res = malloc(row * sizeof(Point3D *));
	for (i = 0; i < row; i++)
	{
		myline = malloc(col * sizeof(Point3D));
		for (j = 0; j < col; j++)
		{
			point.X = g3I[i][j].X * cos(a) - g3I[i][j].Y * sin(a);
			point.Y = g3I[i][j].X * sin(a) + g3I[i][j].Y * cos(a);
			point.Z = (g3I[i][j].Z * altp) / 100;
			myline[j] = point;
		}
		res[i] = myline;
	}
	return (res);
}

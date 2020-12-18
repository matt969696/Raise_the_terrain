# Raise The Terrain
**An isometric projection of a grid that rotates when pressing Right or Left arrow**
****
## About this project
Raise The Terrain is a voluntary project at Holberton School taking part of the "Low-level programming & Algorithm" projects.\
It is created using the **C programming Language** and **SDL2**.
## How it works
 - The program reads the file "altitudes".
 - Gets the altitude of each point.
 - Draws an isometric projection of a grid (64 connected points). Each point has its x, y and z coordinates (z = altitude).
 - Rotates the grid to Right or Left, when the user presses on Right or Left arrow.
 - Quits when the user presses ESC key or when clicks on window Quit button.
## USAGE
You can run this program by following these steps:
> **Step 1:** Clone my repository using this command, (you need to have git, gcc and SDL2 installed on your machine first)
````
git clone
````
> **Step 2:** Change directory to Raise_the_terrain:
````
cd Raise_the_terrain
````
> **Step 3:** Compile the C files in this way:
````
gcc -Wall -Werror -Wextra -pedantic *.c -lm `sdl2-config --cflags` `sdl2-config --libs` -o terrain
````
> **Step 4:** Run the program
````
./terrain altitudes
````
**Exiting the program**
When you want to exit the program, you can use one of the following methods:
> **1: Click on window close button**
````
exit
````
> **2: Press on ESC key**
 - **You can change the name of the program** by typing it instead of "terrain" in compilation step (Step 3).
 - **You can change altitudes of the points of the grid by editing the file "altitudes"** but make sure to keep the same number of integers in the file.
 - **You can also change the name of the file "altitudes"** but make sure to give the new name of the file to your program when you run it "./terrain <new name>".
****

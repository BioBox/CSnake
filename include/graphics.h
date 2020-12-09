// This file includes the graphics and should only be included in main.c
// Anything that needs to be used in main has external linkage

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <time.h>
#ifndef SFML_GRAPHICS_H
#include <SFML/Graphics.h>
#endif

#include "globals.h"
#include "map.h"
#include "snake.h"

#define GRAYNESS 105 // Control the darkness of gray
#define BORDER_COLOR sfWhite
#define BORDER_THICKNESS 5

sfRenderWindow *window;
sfColor sfGray;

// This function allocates all the data for any an all graphics in our game
// Returns a vector giving the size of the window in number of cells
void main_graphicsConstruct();
void main_graphicsDestroy();

// Status, border, nothing
void draw_nothing(void *null, int u, int v);
void draw_upper_status();
void draw_lower_status();
void draw_border();

void draw_game(int draw_option);
void draw_pause();

// Draw sprites. u and v are the locations of where to draw them
// This adds a wall of length 'len' (in cells)
// x and y are the coordinates of the starting position
// line is horizontal if 'horizontal' is true
void add_wall(int x, int y, bool horizontal, int len);

void grow_snake();

void draw_wall(void *, int u, int v);

void add_plant(int x, int y);
void draw_plant(void *, int u, int v);

void add_goodie(int x, int y);
void draw_goodie(void *, int u, int v);
void remove_goodie();

void add_snake_body(int x, int y);
void draw_snake_body(void *, int u, int v);

void add_snake_head(int x, int y);
void draw_snake_head(void *, int u, int v);

void add_snake_tail(int x, int y);
void draw_snake_tail(void *, int u, int v);

#endif // GRAPHICS_H


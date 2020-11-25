// This file includes the graphics and should only be included in main.c
// Anything that needs to be used in main has external linkage

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics>

#define SCREEN_SIZE_X 410
#define SCREEN_SIZE_Y 410
#define CELL_SIZE 40
#define GRAYNESS 105 // Control the darkness of gray
#define BORDER_COLOR "sfWhite"
#define BORDER_THICKNESS 5

sfRenderWindow *window;
sfColor sfGray;

// This function allocates all the data for any an all graphics in our game
// Returns a vector giving the size of the window in number of cells
sfVector2u main_graphicsConstruct();
void main_graphicsDestroy();

// Status, border, nothing
void draw_nothing(int u, int v);
void draw_upper_status();
void draw_lower_status();
void draw_border();

// Draw the whole game
void draw_game(int draw_option);

void draw_img(int u, int v, const char* img);

// Draw sprites. u and v are the locations of where to draw them
void draw_wall(int u, int v);
void draw_plant(int u, int v);
void draw_goodie(int u, int v);
void draw_snake_body(int u, int v);
void draw_snake_head(int u, int v);
void draw_snake_tail(int u, int v);

#endif // GRAPHICS_H

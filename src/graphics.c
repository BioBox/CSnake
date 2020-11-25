// This file implements the graphics
// All of the shapes, spites, and functions for drawing them are defined here.

#include "graphics.h"

sfVertexArray *upper_status_line;
sfVertexArray *lower_status_line;
sfRectangleShape *nborder, *sborder, *eborder, *wborder;
sfRectangleShape *cells[cells_x][cells_y];

sfTexture *snake_head_texture, *snake_tail_texture, *snake_body_texture;
sfTexture *snake_turn_texture;
sfSprite *snake_head_sprite, *snake_tail_sprite, *snake_body_sprite;
sfSprite *snake_turn_sprite;

// Set up all graphics needed
sfVector2i main_graphicsConstruct() {
	unsigned int _cells_x = (int)(SCREEN_SIZE_X/CELL_SIZE);
	unsigned int _cells_y = (int)(SCREEN_SIZE_Y/CELL_SIZE);

	sfGray = sfColor_fromRGB(GRAYNESS, GRAYNESS, GRAYNESS);
	// Create the cells
	for (int i = 0; i<cells_x; i++) {
		for (int j = 0; i<cells_y; i++) {
			cells[i][j] = sfRectangleShape_create();
			sfRectangleShape_setPosition(cells[i][j], (sfVector2f){CELL_SIZE*i,
				CELL_SIZE*j});
			sfRectangleShape_setSize(cells[i][j], (sfVector2f){CELL_SIZE, CELL_SIZE});
			sfRectangleShape_setFillColor(cells[i][j], sfBlack);
		}
	}
	upper_status_line = sfVertexArray_create();
	lower_status_line = sfVertexArray_create();

	sfVertex upper_status_start = {.position = (sfVector2f){0.f, 9.f}, .color = sfGreen};
	sfVertex upper_status_end = {.position = (sfVector2f){0.f, 127.f}, .color = sfGreen};
	sfVertex lower_status_start = {.position = (sfVector2f){0.f, 118.f}, .color = sfGreen};
	sfVertex lower_status_end = {.position = (sfVector2f){127.f, 118.f}, .color = sfGreen};

	sfVertexArray_append(upper_status_line, upper_status_start);
	sfVertexArray_append(upper_status_line, upper_status_end);
	sfVertexArray_append(lower_status_line, lower_status_start);
	sfVertexArray_append(lower_status_line, lower_status_end);

	nborder = sfRectangleShape_create();
	sborder = sfRectangleShape_create();
	eborder = sfRectangleShape_create();
	wborder = sfRectangleShape_create();

	sfRectangleShape_setPosition(nborder, (sfVector2f){0.f, 0.f});
	sfRectangleShape_setPosition(sborder, (sfVector2f){0.f, SCREEN_SIZE_Y-1});
	sfRectangleShape_setPosition(eborder, (sfVector2f){SCREEN_SIZE_X-1, 0.f});
	sfRectangleShape_setPosition(wborder, (sfVector2f){0.f, 0.f});

	sfRectangleShape_setSize(nborder, (sfVector2f){SCREEN_SIZE_X,
		BORDER_THICKNESS});
	sfRectangleShape_setSize(sborder, (sfVector2f){SCREEN_SIZE_X,
		BORDER_THICKNESS});
	sfRectangleShape_setSize(eborder, (sfVector2f){BORDER_THICKNESS,
		SCREEN_SIZE_Y});
	sfRectangleShape_setSize(wborder, (sfVector2f){BORDER_THICKNESS,
		SCREEN_SIZE_Y});
	
	sfRectangleShape_setFillColor(nborder, BORDER_COLOR);
	sfRectangleShape_setFillColor(sborder, BORDER_COLOR);
	sfRectangleShape_setFillColor(eborder, BORDER_COLOR);
	sfRectangleShape_setFillColor(wborder, BORDER_COLOR);

	sfIntRect head = {0, 0, 40, 40};
	sfIntRect tail = {51, 84, 42, 25};
	sfIntRect body = {93, 84, 42, 25};
	sfIntRect turn = {51, 9, 33, 33};

	snake_head_texture = sfTexture_createFromImage("snake_sprite.png", &head);
	snake_tail_texture = sfTexture_createFromImage("snake_sprite.png", &tail);
	snake_body_texture = sfTexture_createFromImage("snake_sprite.png", &body);
	snake_turn_texture = sfTexture_createFromImage("snake_sprite.png", &turn);
	snake_head_sprite = sfSprite_create();
	snake_tail_sprite = sfSprite_create();
	snake_body_sprite = sfSprite_create();
	snake_turn_sprite = sfSprite_create();

	sfSprite_setTexture(snake_head_sprite, snake_head_texture, sfTrue);
	sfSprite_setTexture(snake_tail_sprite, snake_tail_texture, sfTrue);
	sfSprite_setTexture(snake_body_sprite, snake_body_texture, sfTrue);
	sfSprite_setTexture(snake_turn_sprite, snake_turn_texture, sfTrue);

	return (sfVector2u){_cells_x, _cells_y};
}

void main_graphicsDestroy() {
	sfVertexArray_destroy(upper_status_line);
	sfVertexArray_destroy(lower_status_line);

	sfRectangleShape_destroy(nborder);
	sfRectangleShape_destroy(sborder);
	sfRectangleShape_destroy(eborder);
	sfRectangleShape_destroy(wborder);

	// Sprites must be destroyed before textures
	sfSprite_destroy(snake_head_sprite);
	sfSprite_destroy(snake_tail_sprite);
	sfSprite_destroy(snake_body_sprite);
	sfSprite_destroy(snake_turn_sprite);
	sfTexture_destroy(snake_head_texture);
	sfTexture_destroy(snake_tail_texture);
	sfTexture_destroy(snake_body_texture);
	sfTexture_destroy(snake_turn_texture);

	for (int i = 0; i<cells_x; i++) {
		for (int i = 0; i<cells_y; i++) {
			sfRectangleShape_destroy(cells[i][j]);
		}
	}
}

void draw_nothing(int u, int v) {
    sfRectangleShape_setFillColor(cells[u][v], sfTransparent);
	sfRenderWindow_drawRectangleShape(window, cells[u][v], NULL);
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status() {
    // uLCD.line(0, 9, 127, 9, GREEN);
    sfRenderWindow_drawVertexArray(window, upper_status_line);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status() {
    // uLCD.line(0, 118, 127, 118, GREEN);
    sfRenderWindow_drawVertexArray(window, lower_status_line);
}

/**
 * Draw the border for the map.
 */
void draw_border() {
    // uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    // uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    // uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    // uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
    sfRenderWindow_drawRectangeShape(window, nborder, NULL);
    sfRenderWindow_drawRectangeShape(window, sborder, NULL);
    sfRenderWindow_drawRectangeShape(window, eborder, NULL);
    sfRenderWindow_drawRectangeShape(window, wborder, NULL);
}

void draw_game() {
	int half_width = (int)(map_width()/2);
	int half_height = (int)(map_height()/2);
    // Iterate over all visible map tiles
    for (int i = -half_width; i <= half_width; i++) { // Iterate over columns of tiles
        for (int j = -half_height; j <= half_height; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Get the reference point for our screen
            int x = i + snake.head_x;
            int y = j + snake.head_y;

            // Gef the reference point for our previous frame
            int px = i + snake.head_px;
            int py = j + snake.head_py;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

void draw_wall(int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
	sfRectangleShape_setFillColor(cells[i][j], sfGray);
    sfRenderWindow_drawRectangleShape(window, cells[i][j], NULL);
}

// For now imagine it's a flower
void draw_plant(int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRectangleShape_setFillColor(cells[i][j], sfMagenta);
	sfRenderWindow_drawRectangleShape(window, cells[i][j], NULL);
}

void draw_goodie(int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRectangleShape_setFillColor(cells[i][j], sfCyan);
	sfRenderWindow_drawRectangleShape(window, cells[i][j], NULL);
}

void draw_snake_body(int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRectangleShape_setFillColor(cells[i][j], sfGreen);
	sfRenderWindow_drawRectangleShape(window, cells[i][j], NULL);
}

void draw_snake_head(int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfSprite_setPosition(snake_head_sprite, (sfVector2f){CELL_SIZE*u,
		CELL_SIZE*v});
	sfRenderWindow_drawSprite(window, snake_head_sprite);
}

void draw_snake_tail(int u, int v) {
	// uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfSprite_setPosition(snake_head_sprite, (sfVector2f){CELL_SIZE*u,
		CELL_SIZE*v});
	sfRenderWindow_drawSprite(window, snake_tail_sprite);
}



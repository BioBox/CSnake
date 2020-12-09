// This file implements the graphics
// All of the shapes, spites, and functions for drawing them are defined here.

#include "graphics.h"

#define BORDER_COLOR sfWhite

sfVertexArray *upper_status_line;
sfVertexArray *lower_status_line;
sfRectangleShape *nborder, *sborder, *eborder, *wborder;
sfVector2i cells[CELL_X][CELL_Y];

sfTexture *snake_head_texture, *snake_tail_texture, *snake_body_texture;
sfTexture *snake_turn_texture;
sfSprite *snake_head_sprite, *snake_tail_sprite;

sfTexture *plant_texture, *goodie_texture, *wall_texture;
sfCircleShape* menu_selector;

Snake snake;
int random_seed = 0;

void init_main_map() {
	snake_init(&snake);

	random_seed = (int)time(NULL);
	srand(random_seed);
	int goodie_rand = rand() % map_area();

	printf("plants\r\n");

	printf("Adding walls!\r\n");
	add_wall(0,             0,              0,   map_width());
	add_wall(0,             map_height()-1, 0,   map_width());
	add_wall(0,             0,              1,	 map_height());
	add_wall(map_width()-1, 0,              1,   map_height());
	printf("Walls done!\r\n");

	sfVector2i *snells = snake.snake_cells;
	add_snake_head(snells->x, snells->y);
	add_snake_head((snells+1)->x, (snells+1)->y);
	add_snake_head((snells+2)->x, (snells+2)->y);

	printf("Add extra chamber\r\n");
	add_wall(30, 0, 0, 10);
	add_wall(30, 10, 1, 10);
	add_wall(39, 0, 1, 10);
	printf("Added!\r\n");


	// Add stairs to chamber (map 1)
	//add_stairs(15, 5, 1, 5, 5);

	//	  profile_hashtable();
	print_map();
}


// Set up all graphics needed
void main_graphicsConstruct() {
	sfGray = sfColor_fromRGB(GRAYNESS, GRAYNESS, GRAYNESS);
	// Create the cells
	for (int i = 0; i<CELL_X; i++) {
		for (int j = 0; i<CELL_Y; i++) {
			cells[i][j].x = j*CELL_SIZE;
			cells[i][j].y = i*CELL_SIZE;
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

	/* Right now there's just "Start Game" so no need for this rn */
	// Make it relative to the option
	// sfVector2f menu_select_pos = {};
	// menu_selector = sfCircleShape_create();
	// sfCircleShape_setRotation(menu_selector, 90.f);
	// sfCircleShape_setFillColor(menu_selector, sfWhite);
	// sfCircleShape_setScale(menu_selector, (sfVector2f){0.5f, 0.5f});
	// sfCircleShape_setPointCount(menu_selector, 3);
	// sfCircleShape_setPosition(menu_selector, menu_select_pos);
}

void main_graphicsDestroy() {
	sfVertexArray_destroy(upper_status_line);
	sfVertexArray_destroy(lower_status_line);

	sfRectangleShape_destroy(nborder);
	sfRectangleShape_destroy(sborder);
	sfRectangleShape_destroy(eborder);
	sfRectangleShape_destroy(wborder);
}

/**
 * Draw the upper status bar.
 */
void draw_upper_status() {
    // uLCD.line(0, 9, 127, 9, GREEN);
    sfRenderWindow_drawVertexArray(window, upper_status_line, NULL);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status() {
    // uLCD.line(0, 118, 127, 118, GREEN);
    sfRenderWindow_drawVertexArray(window, lower_status_line, NULL);
}

/**
 * Draw the border for the map.
 */
void draw_border() {
    // uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    // uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    // uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    // uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
    sfRenderWindow_drawRectangleShape(window, nborder, NULL);
    sfRenderWindow_drawRectangleShape(window, sborder, NULL);
    sfRenderWindow_drawRectangleShape(window, eborder, NULL);
    sfRenderWindow_drawRectangleShape(window, wborder, NULL);
}

void draw_game(int draw_option) {
	int half_width = (int)(map_width()/2);
	int half_height = (int)(map_height()/2);
    // Iterate over all visible map tiles
    for (int i = -half_width; i <= half_width; i++) {
        for (int j = -half_height; j <= half_height; j++) {
            // Get the reference point for our screen
            int x = i + snake.head_x;
            int y = j + snake.head_y;

            // Gef the reference point for our previous frame
            int px = i + snake.head_px;
            int py = j + snake.head_py;

			int u = (i+5)*CELL_SIZE;
			int v = (j+4)*CELL_SIZE;
            // Figure out what to draw
            DrawFunc draw = NULL;
			MapItem* curr_item;
			MapItem* prev_item;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) {
                curr_item = get_here(x, y);
                prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) {
                    if (curr_item) {
                        draw = curr_item->draw;
                    } else {
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    draw = curr_item->draw;
                }
            } else if (draw_option) {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(curr_item->data, u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

void add_wall(int x, int y, bool horizontal, int len) {
	for(int i = 0; i < len; i++) {
		MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
		w1->type = WALL;
		w1->draw = draw_wall;
		w1->walkable = false;
		w1->data = sfRectangleShape_create();
		unsigned key = (horizontal ? map_2hash(x+i, y) : map_2hash(x, y+i));

		void* val = insertItem(get_active_map()->items, key, w1);
		if (val) free(val); // If something is already there, free it
	}
}

void draw_wall(void *block, int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
    sfRenderWindow_drawRectangleShape(window, block,  NULL);
}

void add_plant(int x, int y) {
	MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
	w1->type = PLANT;
	w1->draw = draw_plant;
	w1->walkable = false;
	w1->data = sfRectangleShape_create();
	sfRectangleShape_setFillColor(w1->data, sfMagenta);
	sfSprite_setPosition(w1->data, (sfVector2f){x*CELL_SIZE, y*CELL_SIZE});

	void* val = insertItem(get_active_map()->items, map_2hash(x, y), w1);
	if (val) free(val); // If something is already there, free it
}

// For now imagine it's a flower
void draw_plant(void *sprite, int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRenderWindow_drawRectangleShape(window, sprite, NULL);
}

void add_goodie(int x, int y) {
	MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
	w1->type = GOODIE;
	w1->draw = draw_goodie;
	w1->walkable = true;
	w1->data = sfSprite_create();
	sfSprite_setPosition(w1->data, (sfVector2f){x*CELL_SIZE, y*CELL_SIZE});
	sfSprite_setTexture(w1->data, goodie_texture, sfFalse);

	void* val = insertItem(get_active_map()->items, map_2hash(x, y), w1);
	if (val) free(val); // If something is already there, free it
}

void draw_goodie(void *sprite, int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRenderWindow_drawSprite(window, sprite, NULL);
}

void remove_goodie(void *sprite) {
	sfSprite_destroy(sprite);
}

void add_snake_body(int x, int y) {
	MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
	w1->type = SNAKE_BODY;
	w1->draw = draw_snake_body;
	w1->walkable = false;
	w1->data = sfSprite_create();
	sfSprite_setPosition(w1->data, (sfVector2f){x*CELL_SIZE, y*CELL_SIZE});
	sfSprite_setTexture(w1->data, snake_body_texture, sfFalse);

	void* val = insertItem(get_active_map()->items, map_2hash(x, y), w1);
	if (val) free(val); // If something is already there, free it
}

void draw_snake_body(void *sprite, int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRenderWindow_drawSprite(window, sprite, NULL);
}

void add_snake_head(int x, int y) {
	MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
	w1->type = SNAKE_BODY;
	w1->draw = draw_snake_head;
	w1->walkable = false;
	w1->data = sfSprite_create();
	sfSprite_setPosition(w1->data, (sfVector2f){x*CELL_SIZE, y*CELL_SIZE});
	sfSprite_setTexture(w1->data, snake_head_texture, sfFalse);

	void* val = insertItem(get_active_map()->items, map_2hash(x, y), w1);
	if (val) free(val); // If something is already there, free it
}

void draw_snake_head(void *sprite, int u, int v) {
    // uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRenderWindow_drawSprite(window, snake_head_sprite, NULL);
}

void add_snake_tail(int x, int y) {
	MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
	w1->type = SNAKE_BODY;
	w1->draw = draw_snake_tail;
	w1->walkable = false;
	w1->data = NULL;

	void* val = insertItem(get_active_map()->items, map_2hash(x, y), w1);
	if (val) free(val); // If something is already there, free it
}

void draw_snake_tail(void *sprite, int u, int v) {
	// uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
	sfRenderWindow_drawSprite(window, snake_tail_sprite, NULL);
}



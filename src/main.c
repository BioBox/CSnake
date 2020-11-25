
#include <SFML/System.h>
#include <SFML/Window.h>

#include "globals.h"
#include "graphics.h"
#include "map.h"
#include "snake.h"

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

extern sfRenderWindow *window;
Snake snake;

// NO NO NO MAKE THIS AN ENUM!
#define NO_RESULT 0
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GAME_OVER 7
#define FULL_DRAW 8

int get_action() {
    if(sfKeyboard_isKeyPressed(sfKeyLeft)) { return GO_LEFT; }
    if(sfKeyboard_isKeyPressed(sfKeyDown)) { return GO_DOWN; }
    if(sfKeyboard_isKeyPressed(sfKeyUp)) { return GO_UP; }
    if(sfKeyboard_isKeyPressed(sfKeyEscape)) { return MENU_BUTTON; }

    return 0;
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the snake position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the snake has not moved.
 */
int update_game(int action) {
    // Check for collision against a wall or enemy
    int at_snake_head = get_here(snake.head_x, snake.head_y)->type;
    if (at_snake_head == WALL) { return GAME_OVER; }
    if (at_snake_head == GOODIE) { return }

    // Check for collision against yourself while updating rest of body and tail
    Coordinate snake_tail = snake.locations[0];
    for (int i = 0; i < snake.length-1; i++) {
	// If true then we're garunteed to hit the body or tail
	if (snake.head_x == snake.locations[i].x && snake.head_y ==
	    snake.locations[i].y) { return GAME_OVER; }
	snake.locations[i].x = snake.locations[i+1].x;
	snake.locations[i].y = snake.locations[i+1].y;
    } // finish updating
    snake.locations[snake.length-1].x = snake.head_px;
    snake.locations[snake.length-1].y = snake.head_py;

    // Update the snake IN THE MAP
    // We'll put in the empty space manually
    MapItem *tailp = get_here(snake_tail.x, snake_tail.y);
    tailp->type = 7;
    tailp->walkable = 1;
    tailp->data = NULL;
    add_snake_head(snake.head_x, snake.head_y);
    add_snake_tail(snake.locations[0].x, snake.locations[0].y);
    add_snake_body(snake.head_px, snake.head_py);

    return 0;
}

void end_game() {
    // Create text object
    sfText *game_over_message = sfText_create();
    sfText_setPosition(game_over_message, (sfVector2i){GAME_OVER_POS_X,
	GAME_OVER_POS_Y)};

    // De-allocate the maps
    for (int i = 0; i < NUM_MAPS; i++) {
	set_active_map(i);
	map_delete();
    }
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawText(window, NULL);
    return;
}

/**
 * Program entry point! This is where it all begins.
 * This function or all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main() {
    // Allolacate data for sprites, shapes, and text
    sfVector2u map_size = snakeGraphicsConstruct();
    // Create hash table for map data
    maps_init();
    // Populate map with stuff
    init_main_map();

    set_active_map(0);
    snake.head_x = snake.head_y = 5;
    draw_game(FULL_DRAW);

    sfClock *gclock = sfClock_create();
    sfTime dt;
    sfInt32 dtmm;

    sfEvent event;
    int action, result;
    while (sfRenderWindow_isOpen(window)) {
	sfClock_restart(gclock);

	while(sfRenderWindow_pollEvent(window, &event)) {
	    action = get_action(inputs);
	    if (event.type == sfEvtclosed) {
		sfRenderWindow_close(window);
	    }
	    if (result == GAME_OVER) {
		end_game();
		return 0;
	    }
	}
	result = update_game(action);
	draw_game(result);

	// Compute update time
	dt = sfClock_restart(gclock);
	dtmm = sfTime_asMilliseconds(dt);
	if (dtmm < 100) { sfSleep(sfTime_asMilliseconds(100 - dtmm)) };
    }
}


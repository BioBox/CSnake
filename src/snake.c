
#include "globals.h"
#include "snake.h"

sfTexture *snake_head_texture;
sfTexture *snake_tail_texture;
sfTexture *snake_body_texture;
sfTexture *snake_turn_texture; // Defaults to 

void snake_init (Snake * s) {
    sfIntRect head = {0, 0, 40, 40};
    sfIntRect tail = {51, 84, 42, 25};
    sfIntRect body = {93, 84, 42, 25};
    sfIntRect turn = {51, 9, 33, 33};

    snake_head_texture = sfTexture_createFromFile(SNAKE_SPRITE_FILE, &head);
    snake_tail_texture = sfTexture_createFromFile(SNAKE_SPRITE_FILE, &tail);
    snake_body_texture = sfTexture_createFromFile(SNAKE_SPRITE_FILE, &body);
    snake_turn_texture = sfTexture_createFromFile(SNAKE_SPRITE_FILE, &turn);
}

void snake_die (Snake *s, death_t death) {
    sfTexture_destroy(snake_head_texture);
    sfTexture_destroy(snake_tail_texture);
    sfTexture_destroy(snake_body_texture);
    sfTexture_destroy(snake_turn_texture);
}

sfVector2i snake_adjust_dir(Snake *s, Orientation dir) {

    switch (dir) {
	case Left:
		if (s->dir == Right) { return (sfVector2i){0, 0}; }
		// Change body texture here
		return (sfVector2i){-1, 0};
	    break;
	case Right:
		if (s->dir == Left) { return (sfVector2i){0, 0}; }
		return (sfVector2i){1, 0};
	    break;
	case Up:
		if (s->dir == Down) { return (sfVector2i){0, 0}; }
		return (sfVector2i){0, -1};
	    break;
	case Down:
		if (s->dir == Up) { return (sfVector2i){0, 0}; }
		return (sfVector2i){0, 1};
	    break;
    }
}

void snake_move(Snake *s, Orientation dir) {
	sfVector2i *snell = s->snake_cells;
	sfVector2i move_dir = snake_adjust_dir(s, dir);
	// The first case is special because you might have to change the textures
	// of the tail and body cell after that
	// Stop once penultimate element has been reached
	for (int i = 0; i<s->length-2; i++) { *snell = *snell++; }
	s->head_px = s->head_x;
	s->head_py = s->head_y;
	s->head_x += move_dir.x;
	s->head_y += move_dir.y;
}

void snake_grown(Snake *s, unsigned int amount) {
	sfVector2i *snell = s->snake_cells;
	
}

void snake_grow(Snake *s) { snake_grown(s, 1); }


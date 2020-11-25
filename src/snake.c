
#include "globals.h"
#include "snake.h"

void snake_init (Snake * s) {
	sfTexture *snake_head_texture;
	sfTexture *snake_head_texture;
	sfTexture *snake_head_texture;
	sfTexture *snake_head_texture;

	sfIntRect head = {0, 0, 40, 40};
	sfIntRect tail = {51, 84, 42, 25};
	sfIntRect body = {93, 84, 42, 25};
	sfIntRect turn = {51, 9, 33, 33};

	snake_head_texture = sfTexture_createFromImage(SNAKE_SPRITE_FILE, &head);
	snake_tail_texture = sfTexture_createFromImage(SNAKE_SPRITE_FILE, &tail);
	snake_body_texture = sfTexture_createFromImage(SNAKE_SPRITE_FILE, &body);
	snake_turn_texture = sfTexture_createFromImage(SNAKE_SPRITE_FILE, &turn);
	snake_head_sprite = sfSprite_create();
	snake_tail_sprite = sfSprite_create();
	snake_body_sprite = sfSprite_create();
	snake_turn_sprite = sfSprite_create();

	sfSprite_setTexture(snake_head_sprite, snake_head_texture, sfTrue);
	sfSprite_setTexture(snake_tail_sprite, snake_tail_texture, sfTrue);
	sfSprite_setTexture(snake_body_sprite, snake_body_texture, sfTrue);
	sfSprite_setTexture(snake_turn_sprite, snake_turn_texture, sfTrue);

}

void snake_die (Snake *s, death_t death) {
	// Sprites must be destroyed before textures
	sfSprite_destroy(snake_head_sprite);
	sfSprite_destroy(snake_tail_sprite);
	sfSprite_destroy(snake_body_sprite);
	sfSprite_destroy(snake_turn_sprite);
	sfTexture_destroy(snake_head_texture);
	sfTexture_destroy(snake_tail_texture);
	sfTexture_destroy(snake_body_texture);
	sfTexture_destroy(snake_turn_texture);
}

sfVector2f snake_move(Snake *s, Orientation dir) {
	switch (dir) {
		case Left:
			snake.head_px = snake.head_x;
			snake.head_x--;
			break;
		case Right:
			snake.head_px = snake.head_x;
			snake.head_x++;
			break;
		case Up:
			snake.head_py = snake.head_y;
			snake.head_y++;
			break;
		case Down:
			snake.head_py = snake.head_y;
			snake.head_y--;
			break;
	}
	return sfSprite_getPosition(snake.head);
}

void snake_grow(Snake *s, unsigned int amount) {

}


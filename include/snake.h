
#ifndef SFML_GRAPHICS_H
#include <SFML/Graphics.h>
#endif

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_SPRITE_FILE "snake_sprite.png"
#define SNAKE_MAX_LENGTH 50

typedef enum { Up, Down, Left, Right } Orientation;
// Snake Structure
typedef struct {
	sfSprite *head;
	sfVector2u headp;
    // This includes the tail but not the head
    sfSprite *snake_cells[SNAKE_MAX_LENGTH];
	unsigned int length;
	sfTexture textures[SNAKE_MAX_LENGTH];
} Snake;

void snake_init (Snake *s);
void snake_die (Snake *s, death_t death);
sfSprite *get_snake_sprite(Snake *s, int l);
void snake_move (Snake *s, Orientation dir);
void snake_grow (Snake *s, unsigned int amount);

#endif


#ifndef SFML_GRAPHICS_H
#include <SFML/Graphics.h>
#endif

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_SPRITE_FILE "media/snake_sprite.png"
#define SNAKE_MAX_LENGTH 50

typedef enum { Normal } death_t;
typedef enum { Up, Down, Left, Right } Orientation;

// Snake Structure
typedef struct {
	// These should be vectors but I don't want to refactor anymore.
	unsigned int head_x, head_y;
	unsigned int head_px, head_py;
	Orientation dir;
    // This includes the tail but not the head
	// The elements go from tail to head
    sfVector2i snake_cells[SNAKE_MAX_LENGTH];
	unsigned int length; // Does not include the head
	sfTexture *textures[SNAKE_MAX_LENGTH];
} Snake;

void snake_init (Snake *s);
void snake_die (Snake *s, death_t death);

// Given a snake structure and direction, it will change the texture of the head
// and the sprite before that to the correct orientation. Returns the direction
// that you'd need to move in as a unit vector
sfVector2i snake_adjust_dir(Snake *s, Orientation dir);

void snake_move (Snake *s, Orientation dir);
// This function replaces move when the snake grows, but you'll have to adjust
// orientation manually
void snake_grown (Snake *s, unsigned int amount);
void snake_grow (Snake *s);

#endif

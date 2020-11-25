
#include "snake.h"

void snake_init (Snake * s)
{
    s->head_x = 7;
    s->head_y = 7;
    s->head_px = 7;
    s->head_py = 7;
    
    s->length = 5;
    
    s->score = 0;
}

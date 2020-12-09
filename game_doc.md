### hash\_table

A hash table. Basically an array of linked lists. Used for handling the map.
Each item in the hash table corresponds to a location in the map. It there's
nothing there, then the hash item points to a vector structure. If there is
something there then it points to a sprite.

### map

This part creates and controls the map, adding and removing things as needed.
The create and destroy functions for every sprite in the game are here. There
are no drawing functions here, but the typedefs for them are.

Every object in the game that will be in map will have a void pointer to the sfml object that it's connected to.

### graphics

This part handles all drawing, so of course it requires access to the window; it
needs the map as well to know where to draw stuff.  The window is declared in
it's header and is created in `main.c`. For every sprite or object in the game,
`graphics.c` will have a function for it. The functions for initializing and
deleting those sprites are in `map.c`.

#### macros
Aside from constructing and deleting all graphics in the game except for the
snake, it also defines the border color and thickness in the header



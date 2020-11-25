
#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <math.h>
#include "snake.h"
#include "hash_table.h"

#define HASH_RANGE 410
#define NUM_MAPS 1
// A structure to represent a map
struct Map;

// Arguments are cell location, not pixel location
typedef void (*DrawFunc)(int u, int v);

// Attributes of an individual cell in the map structure
typedef struct {
    int type; // What is it?
    DrawFunc draw; // How do we draw it?
    int walkable; // Can the snake travel on it?
    void* data; // Extra data
} MapItem;

typedef struct {
    int tm;
    int tx, ty;
} StairsData;

// NO NO NO USE AN ENUMERATION!
#define WALL    0
#define DOOR    1
#define PLANT   2
#define WATER   3
#define KEY     4
#define GOODIE   5
#define SNAKE_BODY   6
#define CLEAR   7
#define STAIRS  8
#define SONAR  9
#define PUZZLE 10
#define NPC 11

// Initialize the maps and set their sizes
// This does NOT create a level on its own. For that look at init_main_map below
void maps_init();

// Populate the level with stuff (including the snake)
void init_main_map();

Map* get_active_map();

// Set the active map with an index and return a pointer to it
Map* set_active_map(int m);

// Return a map pointer via index
Map* get_map(int m);

// Print map to stdout
void print_map();

// How many cells is in the map?
int map_width();
int map_height();
int map_area();

// Get the cell data at the specified location or one ajacent to it
MapItem* get_here(int x, int y);
MapItem* get_north(int x, int y);
MapItem* get_south(int x, int y);
MapItem* get_east(int x, int y);
MapItem* get_west(int x, int y);

// Delete a map cell from the hashtable.
// It may be better to simply draw a black square onto it instead
void map_erase(int x, int y);

// Delete active map
void map_delete();

// The rest of these are designed to erase anything taht's already there

// This adds a wall of length 'len' (in cells)
// x and y are the coordinates of the starting position
// line is horizontal if 'horizontal' is true
void add_wall(int x, int y, bool horizontal, int len);

/**
 * Add a PLANT item at (x,y). If there is already a MapItem at (x,y), erase it
 * before adding the plant.
 */
void add_plant(int x, int y);
void add_goodie(int x, int y);
void remove_goodie(int x, int y);
void add_snake_body(int x, int y);
void add_snake_head(int x, int y);
void add_snake_tail(int x, int y);

#endif //MAP_H

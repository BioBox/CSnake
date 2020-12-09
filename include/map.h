
#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef SFML_GRAPHICS_H
#include <SFML/Graphics.h>
#endif

#include "hash_table.h"

#define HASH_RANGE 410
#define NUM_MAPS 1
// A structure to represent a map
typedef struct {
	HashTable* items;
	int w, h;
} Map;


// Arguments are cell location, not pixel location
typedef void (*DrawFunc)(void *sprite, int u, int v);
typedef void (*DestroyFunc)();

// Attributes of an individual cell in the map structure
// If nothing's there, then the draw and destroy functions aren't there
// There is no position attribute because that's the only way to get a certain
// cell. There's no create function because why not do that when the type is
// set?
typedef struct {
	int type; // What is it? Same as file name.
	sfSprite *sprite;
	DrawFunc draw; // How do we draw it?
	DestroyFunc destroy; // How to destroy it?
	bool walkable; // Can the snake travel on it?
	void* data; // Extra data
} MapItem;

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

unsigned map_hash(unsigned key);
unsigned map_2hash(int x, int y);

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

#endif //MAP_H

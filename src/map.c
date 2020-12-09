// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "map.h"

static Map maps[NUM_MAPS];
static int active_map = 0;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
	return (get_active_map())->w*Y + X;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key) {
	return key % HASH_RANGE;
}

unsigned map_2hash(int x, int y) {
	return XY_KEY(x, y) % HASH_RANGE;
}

void maps_init(unsigned int w, unsigned int h) {
	// Initialize hash table
	// Set width & height
	Map *a_map = get_active_map();
	a_map->items = createHashTable(map_hash, HASH_RANGE);
	a_map->w = w;
	a_map->h = h;
}

Map* get_active_map() {
	return maps + active_map;
}

Map* set_active_map(int m) {
	active_map = m;
	return &maps[active_map];
}

void print_map() {
	char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
	Map* map = get_active_map();
	for(int j = 0; j < map->h; j++) {
		for (int i = 0; i < map->w; i++) {
			MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
			if (item) printf("%c", lookup[item->type]);
			else printf(" ");
		}
		printf("\r\n");
	}
}

int map_width() {
	return get_active_map()->w;
}

int map_height() {
	return get_active_map()->h;
}

int map_area() {
	Map *a_map = get_active_map();
	return (a_map->h)*(a_map->w);
}


MapItem* get_north(int x, int y) { return get_here(x, y-1); }
MapItem* get_south(int x, int y) { return get_here(x, y+1); }
MapItem* get_east(int x, int y)  { return get_here(x+1, y); }
MapItem* get_west(int x, int y)  { return get_here(x-1, y); }
MapItem* get_here(int x, int y)  { return (MapItem *)getItem(get_active_map()->items, XY_KEY(x, y)); }

void map_erase(int x, int y) {
	deleteItem(get_active_map()->items, XY_KEY(x, y));
}

void map_delete() { destroyHashTable(get_active_map()->items); }


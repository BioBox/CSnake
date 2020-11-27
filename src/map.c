// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "map.h"

int random_seed = 0;
Snake *snake;

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

static Map maps[NUM_MAPS];
static int active_map = 0;

static const MapItem CLEAR_SENTINEL = {
    .type = CLEAR,
    .draw = draw_nothing
};

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
     return get_active_map()->w*Y + X;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key) {
    return key % HASH_RANGE;
}

void maps_init(unsigned int w, unsigned int h) {
    // Initialize hash table
    // Set width & height
    Map *a_map = get_active_map();
    a_map->items = createHashTable(map_hash, HASH_RANGE);
	a_map->w = w;
	a_map->h = h;
}

void init_main_map() {
    snake_init(&snake);

	random_seed = time(NULL);
	srand(random_seed);
	goodie_rand = rand() % map_area();
	
    printf("plants\r\n");

    printf("Adding walls!\r\n");
	add_wall(0,             0,              0,   map_width());
	add_wall(0,             map_height()-1, 0,   map_width());
	add_wall(0,             0,              1,	 map_height());
    add_wall(map_width()-1, 0,              1,   map_height());
    printf("Walls done!\r\n");

    add_snake_head(snake.locations[0].x, snake.locations[0].y);
    add_snake_body(snake.locations[1].x, snake.locations[1].y);
    add_snake_tail(snake.locations[2].x, snake.locations[2].y);

    printf("Add extra chamber\r\n");
    add_wall(30, 0, 0, 10);
    add_wall(30, 10, 1, 10);
    add_wall(39, 0, 1, 10);
    printf("Added!\r\n");


    // Add stairs to chamber (map 1)
    //add_stairs(15, 5, 1, 5, 5);

    //	  profile_hashtable();
    print_map();
}

Map* get_active_map() {
    return &maps[active_map];
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

void add_wall(int x, int y, bool horizontal, int len) {
    for(int i = 0; i < len; i++) {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (horizontal ? XY_KEY(x+i, y) : XY_KEY(x, y+i));
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_goodie(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GOODIE;
    w1->draw = draw_goodie;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void remove_goodie(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_body(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_body;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_head(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_head;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_tail(int x, int y) {
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_tail;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}


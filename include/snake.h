
#define SNAKE_MAX_LENGTH 50
#define SNAKE_START_X 5 // Starting position for head
#define SNAKE_START_Y 5
#define SNAKE_START_LEN 2 // Doesn't include head or

// Structure of coordinates in the map
typedef struct{
    int x;
    int y;
} Coordinate;

// Snake Structure
typedef struct {
    int head_x, head_y, head_px, head_py; // Location of the head of the snake
    int length; // length of the snake
    // Snake body locations
    // This includes the tail but not the head
    Coordinate locations[SNAKE_MAX_LENGTH];
    int score; //Current score of the snake
} Snake;

// Initialize a snake structure
// You want to assign initial values to each of the variables defined above
// in the snake structure.
void snake_init (Snake * snake);

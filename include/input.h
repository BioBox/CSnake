
#ifndef HARDWARE_H
#define HARDWARE_H

#include <SFML/Window.h>

struct GameInputs {
    int b1, b2, b3, b4;     // Button presses
};

/**
 * Read all the user inputs. 
 * This is all input hardware interaction should happen.
 * Returns a GameInputs struct that has all the inputs recorded.
 * This GameInputs is used elsewhere to compute the game update.
 */
GameInputs read_inputs();

#endif // HARDWARE_H

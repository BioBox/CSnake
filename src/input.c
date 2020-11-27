
#include "hardware.h"

GameInputs read_inputs() 
{
    GameInputs in;
    in.b1 = button1;
    in.b2 = button2;
    in.b3 = button3;
    acc.readXYZGravity(&in.ax, &in.ay, &in.az);
    return in;
}

// This declares all extens and a few assertion macros
#ifndef GLOBAL_H
#define GLOBAL_H

// 
// Global settings
#define BACKGROUND_COLOR 0x000000 //black
#define LANDSCAPE_HEIGHT 4        // number of pixel on the screen
#define MAX_BUILDING_HEIGHT 10    // number of pixel on the screen


// === [define the macro of error heandle function] ===
// when the condition (c) is not true, assert the program and show error code
#define ASSERT_P(c,e) do { \
    if(!(c)){ \
        pc.printf("\nERROR:%d\n",e); \
        while(1); \
    } \
} while (0)

// === [error code] ===
#define ERROR_NONE 0 // All good in the hood
#define ERROR_MEH -1 // This is how errors are done

#endif //GLOBAL_H

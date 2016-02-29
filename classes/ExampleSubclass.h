//
//  Scorpion.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>
#include "Create.h"

typedef struct Scorpion {
    // "Inheriting" from Create
    Create create;

    // Custom properties/instance methods
    void (*test)();
} Scorpion;

extern Scorpion new_scorpion(); // constructor

// Global scorpion object - only way??
Scorpion scorpion;

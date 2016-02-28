//
//  Scorpion.c
//  Source written by Justin Yu
//

#include "Scorpion.h"
#include <math.h>

static void test() {
    scorpion.create.right(90, 0, 100);
}

Scorpion new_scorpion() {
    Scorpion instance = {
        // Assign instance properties
        .test = &test
    };
    instance.create = new_create();
    return instance;
}

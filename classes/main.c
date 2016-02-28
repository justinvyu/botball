//
//  main.c
//  Source written by Justin Yu
//

#include <kipr/botball.h>
#include "CreateExampleSubclass.h"

int main() {
    scorpion = new_scorpion(); // instantiate scorpion

    scorpion.create.connect(); // access "inherited methods" from Create.h

    scorpion.test(); // instance method in CreateExampleSubclass.h

    scorpion.create.disconnect(); // access "inherited methods" from Create.h

    return 0;
}

//
//  Scorpion.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>
#include "Create.h"
#include "Controller.h"

// TODO: Enums
#define BACK_SERVO 2
#define ARM_SERVO 0
#define CLAW_SERVO 1

#define ARM_UP_UP 0
#define ARM_UP 200
#define ARM_DOWN 2047

#define CLAW_OPEN 1850
#define CLAW_PARTIAL 1200
#define CLAW_CLOSED 50

#define BACK_UP 826
#define BACK_DOWN 1100

typedef struct Scorpion {
    // Inheriting from Create
    Create create;
    Controller controller;

    // Custom properties/instance methods
    void (*grab_tribbles)();
    void (*shake_arm)();

    void (*lower_arm)();
    void (*raise_arm)();

    void (*close_claw)();
    void (*close_claw_slow)(float time);
    void (*open_claw)();
    void (*set_claw_to_position)(int position);
} Scorpion;

extern Scorpion new_scorpion(); // constructor

// Global scorpion object
Scorpion scorpion;

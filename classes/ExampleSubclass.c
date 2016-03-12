//
//  Scorpion.c
//  Source written by Justin Yu
//

#include "Scorpion.h"
#include <math.h>

// custom subroutines

static void shake_arm() {
    int i;
    for(i = 0; i < 3; i++) {
        scorpion.controller.servo(ARM_SERVO, ARM_UP_UP);
        msleep(200);
        scorpion.controller.servo(ARM_SERVO, ARM_UP);
        msleep(200);
    }
}

static void lower_arm() {
    scorpion.controller.servo(ARM_SERVO, ARM_DOWN);
    msleep(200);
}

static void raise_arm() {
    scorpion.controller.servo(ARM_SERVO, ARM_UP);
    msleep(200);
}

static void open_claw() {
    scorpion.controller.servo(CLAW_SERVO, CLAW_OPEN);
    msleep(200);
}

static void close_claw() {
    scorpion.controller.servo(CLAW_SERVO, CLAW_CLOSED);
    msleep(200);
}

static void close_claw_slow(float time) {
    scorpion.controller.slow_servo(CLAW_SERVO, CLAW_CLOSED, time);
}

static void set_claw_to_position(int position) {
    scorpion.controller.servo(CLAW_SERVO, position);
    msleep(200);
}

static void grab_tribbles() {
    scorpion.set_claw_to_position(CLAW_PARTIAL);
    scorpion.create.forward(10, 100);
    scorpion.close_claw_slow(1.2);
}

Scorpion new_scorpion() {
	Scorpion instance = {
        // Assign instance properties
        .grab_tribbles = &grab_tribbles,
        .shake_arm = &shake_arm,
        .lower_arm = &lower_arm,
        .raise_arm = &raise_arm,
        .open_claw = &open_claw,
        .close_claw = &close_claw,
        .close_claw_slow = &close_claw_slow,
        .set_claw_to_position = &set_claw_to_position
    };
    instance.create = new_create();
    instance.controller = new_create_controller();
    return instance;
}

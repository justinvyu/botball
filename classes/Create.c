//
//  Create.c
//  Source written by Justin Yu
//

#include "Create.h"
#include <math.h>

// Methods Prototypes
static void create_write_int(int decimal);
static void forward(float dist, int speed);
static void backward(float dist, int speed);
static void left(int angle, float radius, int speed);
static void right(int angle, float radius, int speed);

// Number of "create ticks" per centimeter moved
#define CTICK_PER_CM 10.0

#define get_high_byte(byte) ((byte >> 8) & 255)
#define get_low_byte(byte) (byte & 255)

static void create_write_int(int decimal) {
    // [high byte][low byte]
    create_write_byte(get_high_byte(decimal));
    create_write_byte(get_low_byte(decimal));
}

static void forward(float dist, int speed) {
    if(speed < -500 || speed > 500)
        return;
    if(dist < 0.) {
        backward(-dist, speed);
        return;
    }

    set_create_distance(0);
    long ticks = dist * CTICK_PER_CM;
    create_drive_direct(speed, speed);

    do {
        msleep(40);
    } while(get_create_distance() < ticks);

    create_stop();
}

static void backward(float dist, int speed) {
    if(speed < -500 || speed > 500)
        return;
    if(dist < 0.) {
        forward(-dist, speed);
        return;
    }

    set_create_distance(0);
    long ticks = -dist * CTICK_PER_CM;

    create_drive_direct(-speed, -speed);

    do {
        msleep(40);
    } while(get_create_distance() > ticks);

    create_stop();
}

static void left(int angle, float radius, int speed) {
    if(radius < 0.)
        return;
    if (speed < -500 || speed > 500)
        return;
    if(angle < 0.) {
        right(-angle, radius, speed);
        return;
    }

    long radiusTicks = radius * CTICK_PER_CM;
    set_create_total_angle(0);

    // create turn byte (decimal): 137
    // [137][speed high][speed low][radius high][radius low]
    create_write_byte(137);
    create_write_int(speed);
    if(radius == 0)
        create_write_int(1);
    else
        create_write_int(radiusTicks);

    do {
        msleep(40);
    } while(get_create_total_angle() <= angle);

    create_stop();
}

static void right(int angle, float radius, int speed) {
    if(radius < 0.)
        return;
    if (speed < -500 || speed > 500)
        return;
    if(angle < 0.) {
        left(-angle, radius, speed);
        return;
    }

    long radiusTicks = radius * CTICK_PER_CM;
    set_create_total_angle(0);

    // create turn byte (decimal): 137
    // [137][speed high][speed low][radius high][radius low]
    create_write_byte(137);
    create_write_int(speed);

    if(radius == 0)
        create_write_int(-1);
    else
        create_write_int(-radiusTicks);

    do {
        msleep(40);
    } while(get_create_total_angle() > -angle);

    create_stop();
}

Create new_create() {
    Create instance = {
        // Assign method references
        .forward = &forward,
        .backward = &backward,
        .left = &left,
        .right = &right,
        .drive_direct = &create_drive_direct,
        .stop = &create_stop,
        .get_distance = &get_create_distance,
        .set_distance = &set_create_distance,
        .get_total_angle = &get_create_total_angle,
        .set_total_angle = &set_create_total_angle,
        .get_lbump = &get_create_lbump,
        .get_rbump = &get_create_rbump,
        .write_byte = &create_write_byte,
        .write_int = &create_write_int,
        .get_battery_charge = &get_create_battery_charge,
        .full = &create_full,
        .connect = &create_connect,
        .disconnect = &create_disconnect
    };
    return instance;
}

/*
static struct Create new() {
    return (struct Create) {
        .forward = &forward,
        .backward = &backward,
        .left = &left,
        .right = &right
    };
}

const struct CreateClass Create = {
    .new = &new,
    .write_int = &create_write_int
};
*/

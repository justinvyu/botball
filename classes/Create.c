//
//  Create.c
//  Source written by Justin Yu
//

#include "Create.h"
#include <math.h>

// Number of "create ticks" per centimeter moved
#define CTICK_PER_CM 9.6
/*
#define get_high_byte(byte) ((byte >> 8) & 255)
#define get_low_byte(byte) (byte & 255)

void create_write_int(int value) {
  	// [high byte][low byte]
    create_write_byte(get_high_byte(value));
    create_write_byte(get_low_byte(value));
}
*/
static void forward(float dist, int speed) {
    if(speed < -500 || speed > 500)
        return;
    if(dist < 0.) {
        return;
    }

    set_create_distance(0);
    long ticks = dist * CTICK_PER_CM;
    create_drive_direct(speed, speed);

    while(get_create_distance() < ticks)
        msleep(10);

    create_stop();
}

static void backward(float dist, int speed) {
    if(speed < -500 || speed > 500)
        return;
    if(dist < 0.)
        return;

	set_create_distance(0);
    long ticks = -dist * CTICK_PER_CM;

    create_drive_direct(-speed, -speed);

    while(get_create_distance() > ticks)
        msleep(10);

    create_stop();
}

static void left(int angle, float radius, int speed) {
    if(radius < 0.)
        return;
    if (speed < -500 || speed > 500)
        return;

    if(angle < 0.)
        return;

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

    while(get_create_total_angle() < angle)
        msleep(10);

    create_stop();
}

static void right(int angle, float radius, int speed) {
    if(radius < 0.)
        return;
    if (speed < -500 || speed > 500)
        return;
    if(angle < 0.)
        return;

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

    while(get_create_total_angle() > -angle)
        msleep(10);

    create_stop();
}

static struct Create new() {
	return (struct Create) {
        .forward = &forward,
        .backward = &backward,
        .left = &left,
        .right = &right
    };
}

const struct CreateClass Create = {
    .new = &new
};

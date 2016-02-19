//
//  create.c
//  Source written by Justin Yu
//

#include "create.h"
#include <math.h>

// Number of "create ticks" per centimeter moved
#define CTICK_PER_CM 9.6

// Clearing Create measured values (distance traveled & angle turned)

void clear_create_distance() {
    set_create_distance(0);
}

void clear_create_angle() {
    set_create_total_angle(0);
}

// iRobot2 Open Interface : https://www.adafruit.com/datasheets/create_2_Open_Interface_Spec.pdf

#define get_high_byte(byte) ((byte >> 8) & 255)
#define get_low_byte(byte) (byte & 255)

void create_write_int(int value) {
  	// [high byte][low byte]
    create_write_byte(get_high_byte(value));
    create_write_byte(get_low_byte(value));
}

// Helper Conversions (converting "create ticks" to centimeters)

float CTICKtoCM(long tick) {
    return (float)(tick / CTICK_PER_CM);
}

long CMtoCTICK(float cm) {
    return (long)(cm * CTICK_PER_CM);
}

// Create General Movement

void create_left(int angle, float radius, int speed) {
    if(radius < 0.)
        return;
    if (speed < -500 || speed > 500)
        return;

    if(angle < 0.) {
        create_right(-angle, radius, speed);
        return;
    }

    long radiusTicks = CMtoCTICK(radius);

    clear_create_angle();

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

void create_right(int angle, float radius, int speed) {
    if(radius < 0.)
        return;
    if (speed < -500 || speed > 500)
        return;

    if(angle < 0.) {
        create_left(-angle, radius, speed);
        return;
    }

    long radiusTicks = CMtoCTICK(radius);

    clear_create_angle();

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

void create_forward(float dist, int speed) {
    if(speed < -500 || speed > 500)
        return;

    if(dist < 0.) {
        create_backward(-dist, speed);
        return;
    }

    clear_create_distance();
    long ticks = CMtoCTICK(dist);

    create_drive_direct(speed, speed);

    while(get_create_distance() < ticks)
        msleep(10);

    create_stop();
}

void create_backward(float dist, int speed) {
    if(speed < -500 || speed > 500)
        return;

    if(dist < 0.) {
        create_forward(-dist, speed);
        return;
    }

    clear_create_distance();
    long ticks = CMtoCTICK(-dist);

    create_drive_direct(-speed, -speed);

    while(get_create_distance() > ticks)
        msleep(10);

    create_stop();
}

// Sensor Integrations

void create_forward_until_bump(int speed) {
    create_drive_direct(speed, speed);

    while(get_create_lbump() == 0 && get_create_rbump() == 0)
        msleep(10);

    create_stop();
}

// Misc. Functions -- UNTESTED

void create_send() {
    create_write_byte(142); // Sensor input
    create_write_byte(35);	// 35 : OI Mode
}

void create_receive() {
    char buffer[1];
    char *bptr = buffer;
    create_read_block(bptr, 1);
}

void create_block() {
    create_stop();
    create_send();
    create_receive();
}

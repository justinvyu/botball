//
//  Create.h
//  Source written by Justin Yu
//

#ifndef _CREATE_H_
#define _CREATE_H_

#include <kipr/botball.h>

struct Create {
    void (*forward)(float dist, int speed);
    void (*backward)(float dist, int speed);
    void (*left)(int angle, float radius, int speed);
    void (*right)(int angle, float radius, int speed);
};

extern const struct CreateClass {
    // Constructor
    struct Create (*new)();

    // Class Methods
    // void (*write_int)(int decimal);
} Create;

#endif

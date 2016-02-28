//
//  Create.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>

typedef struct Create {
    // movement
    void (*forward)(float dist, int speed);
    void (*backward)(float dist, int speed);
    void (*left)(int angle, float radius, int speed);
    void (*right)(int angle, float radius, int speed);

    void (*drive_direct)(int l_speed, int r_speed);
    void (*stop)();

    // sensors
    int (*get_distance)();
    void (*set_distance)(int dist);

    int (*get_total_angle)();
    void (*set_total_angle)(int angle);

    int (*get_lbump)();
    int (*get_rbump)();

    // OI
    void (*write_byte)(char byte);
    void (*write_int)(int decimal);

    // misc
    int (*get_battery_charge)();
    void (*full)();
    int (*connect)();
    void (*disconnect)();
} Create;

extern Create new_create(); // constructor

/*
extern const struct CreateClass {
    // Constructor
    struct Create (*new)();

    // Class Methods
    void (*write_int)(int decimal);
} Create;
*/

/*
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
    void (*write_int)(int decimal);
} Create;
*/

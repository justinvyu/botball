//
//  Controller.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>

#define PI 3.14159265358979

typedef struct Controller {
    int motor_left, motor_right;
    float distance_between_wheels;
    float wheel_diameter;

    // setters
    int (*set_motor_left)(int port); // returns 0 if it fails; 1 if it succeeds
    int (*set_motor_right)(int port);

    // motors
    void (*forward)(float dist, int speed);
    void (*backward)(float dist, int speed);
    void (*left)(int angle, float radius, int speed);
    void (*right)(int angle, float radius, int speed);

    void (*motor)(int motor, int percent); // percent from -100 to 100
    int (*mav)(int motor, int velocity);
    int (*mtp)(int motor, int speed, int goal_pos);
    int (*mrp)(int motor, int speed, int delta_pos);

    void (*stop)();
    void (*motor_off)(int motor);

    int (*get_motor_position_counter)(int motor);
    void (*clear_motor_position_counter)(int motor);
    int (*gmpc)(int motor); // shorthand
    void (*cmpc)(int motor);

    // servos
    void (*enable_servo)(int port);
    void (*disable_servo)(int port);
    void (*enable_servos)();
    void (*disable_servos)();
    int (*get_servo_position)(int port);
    void (*set_servo_position)(int port, int position);
    void (*slow_servo)(int port, int position, float time);

    // digital sensors
    int (*digital)(int port); // returns either 0 or 1

    // analog sensors
    int (*analog)(int port);
    int (*analog8)(int port);
    int (*analog10)(int port); // usually use this
    int (*analog_et)(int port);

} Controller;

// constructor
extern Controller new_wallaby(int motor_left, int motor_right,
                           int distance_between_wheels, int wheel_diameter);
extern Controller new_create_wallaby(); // alternate constructor

Controller controller; // global wallaby instance

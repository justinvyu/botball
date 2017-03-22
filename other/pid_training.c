#include <kipr/botball.h>
#include "Controller.h"

enum Side {
    LEFT = 0,
    RIGHT = 1
};

/**
 *  line_follow(int distance_in_ticks) function by Justin Yu 3/14 
 *  --------------------------------------------------------------
 *  This function uses a PID controller to follow a line for a
 *  specified distance, stopping when the motor position counter
 *  reaches the input `distance_in_ticks` parameter. The P controller calculates
 *  the error between the current sensor value and the desired threshold
 *  value. The I controller calculates a running total of error. The
 *  D controller calculates the change in error from iteration to iteration.
 *  These three, multiplied by experimentally defined constants and summed,
 *  create a turn variable that alters the speed of both motors (0 and 1).
 */
void line_follow(int distance_in_ticks) {
    float kp = 2.4,   // proportional constant
          ki = 0.1,   // integral constant
          kd = 8.2;   // derivative constant
    
    float integral_scalar = 7 / 8.;

    int last_error = 0;
    int speed = 1000;    // velocity of motors at error = 0
    int threshold = 800; // experimentally determined white/black threshold
    
    clear_motor_position_counter(MOTOR_LEFT);
    clear_motor_position_counter(MOTOR_RIGHT);
    while(get_motor_position_counter(MOTOR_LEFT) < distance_in_ticks
          && get_motor_position_counter(MOTOR_RIGHT) < distance_in_ticks) {
        sensor_value = analog10(tophat);

        error = sensor_value - threshold;                  // P
        integral = integral_scalar * integral + error;     // I
        derivative = error - last_error;                   // D

        turn = (int)(kp * error + ki * integral + kd * derivative);
        mav(MOTOR_LEFT, speed - turn); // power left motor
        mav(MOTOR_RIGHT, speed + turn); // power right motor
        last_error = error;
        msleep(1);
    }
}

int main()
{
    controller = new_controller(0, 1, 14.5, 5.0);

    // initialize variables

    enum Side side;

    int tophat = 5;
    int et = 1, et_threshold = 1700; // greater than 1600 means that the pole is there

    // PID

    int low, high;
    float offset = 0; // average of white and black sensor values (660, 985) = 822.5
    float integral = 0; // running total of errors
    float last_error = 0;
    float derivative = 0; // current error - last error

    int sensor_value, turn;
    float error;

    // calibration

    printf("Place tophat sensor above black line.\n");
    while(1) {
        if(digital(0) == 1) {
            high = analog10(tophat);
            break;
        }
        msleep(10);
    }

    msleep(1000);

    printf("Place tophat sensor above white space.\n");

    while(1) {
        if(digital(0) == 1) {
            low = analog10(tophat);
            break;
        }
        msleep(10);
    }

    msleep(1000);

    printf("Place tophat sensor above white space.\n");

    while(digital(0) == 0);

    float kp = 2.4,   // proportional constant
          ki = 0.1,   // integral constant
          kd = 8.2;   // derivative constant

    int last_error = 0;
    int speed = 1000; // velocity of motors at error = 0
    int threshold = 800;
    
    while(1) {
        sensor_value = analog10(tophat);

        error = sensor_value - threshold;            // P
        integral = (7. / 8.) * integral + error;     // I
        derivative = error - last_error;             // D

        turn = (int)(kp * error + ki * integral + kd * derivative);
        mav(0, speed - turn); // power left motor
        mav(1, speed + turn); // power right motor
        last_error = error;
        msleep(1);
    }

    return 0;
}

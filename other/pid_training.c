#include <kipr/botball.h>
#include "Controller.h"

enum Side {
    LEFT = 0,
    RIGHT = 1
};

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

    int speed = 1000; // velocity of motors at error = 0
    offset = (float)(low + high) / 2.; // average of the calibration readings

    while(1) {
        sensor_value = analog10(tophat);

        error = sensor_value - offset;
        integral = (7. / 8.) * integral + error;
        derivative = error - last_error;

        turn = (int)(kp * error + ki * integral + kd * derivative);

        mav(0, speed - turn); // left motor
        mav(1, speed + turn); // right motor

        last_error = error;

        msleep(1);
    }

    return 0;
}

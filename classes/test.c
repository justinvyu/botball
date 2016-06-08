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

    // PID

    float threshold;
    int low, high;
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

    threshold = (float)(low + high) / 2.;

    msleep(1000);
    printf("Ready.\n");

    while(digital(0) == 0);

    motor(controller.motor_left, 70);
    motor(controller.motor_right, 70);
    controller.cmpc(controller.motor_left);
    controller.cmpc(controller.motor_right);
    while(1) {
        if(analog10(tophat) > threshold) {
            motor(controller.motor_right, -50);
            motor(controller.motor_left, 90);
        } else {
            motor(controller.motor_left, 70);
            motor(controller.motor_right, 190);
        }
        msleep(50);
    }

    return 0;
}

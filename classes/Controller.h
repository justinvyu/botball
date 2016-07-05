//
//  Controller.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>

/**
 * Controller
 *
 * This is a class for the robot's controller (ie: the Wallaby).
 * It includes methods to move motors, servos, and access sensors.
 */
typedef struct Controller {

    // INSTANCE VARIABLES:

    int motor_left;
    int motor_right;
    float distance_between_wheels;
    float wheel_diameter;

    // INSTANCE METHODS:

    // MOTORS

    /**
     * Move the robot forward
     * @param dist  the distance you want the robot to move in cm
     * @param speed the robot's speed (a value from 1-100)
     */
    void (*forward)(float dist, int speed);

    /**
     * Move the robot backward
     * @param dist  the distance you want the robot to move in cm
     * @param speed the robot's speed (a value from 1-100)
     */
    void (*backward)(float dist, int speed);

    /**
     * Turn the robot left
     * @param angle  the angle you want the robot to turn in degrees
     * @param radius the radius of the turn (relative to the right wheel)
     * @param speed  the robot's speed (from 1-100)
     */
    void (*left)(int angle, float radius, int speed);

    /**
     * Turn the robot right
     * @param angle  the angle you want the robot to turn in degrees
     * @param radius the radius of the turn (relative to the left wheel)
     * @param speed  the robot's speed (from 1-100)
     */
    void (*right)(int angle, float radius, int speed);

    /**
     * Power a motor
     * @param motor    the motor port you want to power
     * @param percent  the robot's speed as a percent
     */
    void (*motor)(int motor, int percent);

    int (*mav)(int motor, int velocity);
    int (*mtp)(int motor, int speed, int goal_pos);
    int (*mrp)(int motor, int speed, int delta_pos);

    /**
     * Stops all motors
     */
    void (*stop)();

    /**
     * Turns an individual motor off
     * @param motor  the motor port that you want to turn off
     */
    void (*motor_off)(int motor);

    /**
     * Find how much a motor has turned (from its internal sensor)
     * @param motor  the motor port you want to access
     * @return       how much the motor has turned in BackEMF ticks
     */
    int (*get_motor_position_counter)(int motor);

    /**
     * Clear a motor's position counter to 0
     * @param motor  the motor port you want to access
     */
    void (*clear_motor_position_counter)(int motor);

    int (*gmpc)(int motor); // see `get_motor_position_counter`
    void (*cmpc)(int motor); // see `clear_motor_position_counter`

    // SERVOS

    /**
     * Enables an individual servo
     * @param port  the servo port you want to enable
     */
    void (*enable_servo)(int port);

    /**
     * Disables an individual servo
     * @param port  the servo port you want to disable
     */
    void (*disable_servo)(int port);

    /**
     * Enables all servos
     */
    void (*enable_servos)();

    /**
     * Disables all servos
     */
    void (*disable_servos)();

    /**
     * Find the value of a servo
     * @param port  the servo port you want to access
     * @return      the position of the servo from 0-2047
     */
    int (*get_servo_position)(int port);

    /**
     * Set the position of a servo (same as set_servo_position)
     * @param port      the servo port you want to set
     * @param position  the position you want the servo to be set
     */
    void (*servo)(int port, int position);

    /**
     * Sets a servo position with a given duration
     * STILL UNDER DEVELOPMENT
     * @param port      the servo you want to set
     * @param position  the position you want the servo to be set
     * @param time      how long the servo takes to reach the desired position
     */
    void (*slow_servo)(int port, int position, float time);

    // DIGITAL SENSORS

    /**
     * Find the value of a digital sensor
     * @param port  the port of the digital sensor (ports from 0-9)
     * @return      the value of the digial sensor (0 or 1)
     *              a `0` means that the digial sensor is not pressed
     *              a `1` means that the digital sensor is pressed
     */
    int (*digital)(int port);

    // ANALOG SENSORS

    /**
     * Find the 8-bit analog value for a sensor
     * @param port  the port of the analog sensor (ports from 0-5)
     * @return      the 8-bit analog value (a range of 0-255)
     */
    int (*analog)(int port);

    /**
     * Find the 10-bit analog value for a sensor
     * @param port  the port of the analog sensor (ports from 0-5)
     * @return      the 10-bit analog value (a range of 0-1023)
     */
    int (*analog10)(int port);

    /**
     * Find the analog value for an et sensor
     * @param port  the port of the et sensor
     * @return      the 8-bit analog value of the et sensor (a range of 0-255)
     */
    int (*analog_et)(int port);

} Controller;

// constructor

/**
 * Create an instance of Controller
 * @param  motor_left              the motor port for the left wheel
 * @param  motor_right             the motor port for the right wheel
 * @param  distance_between_wheels the distance in centimeters between the wheels
 * @param  wheel_diameter          the diameter of either wheel
 * @return                         the Controller instance
 */
extern Controller new_controller(int motor_left, int motor_right, 
                                float distance_between_wheels, float wheel_diameter);

/**
 * ALTERNATE CONSTRUCTOR:
 * Creates an instance of Controller that is attached to a create and does
 * not require a left/right motor.
 * @return the Controller instance
 */
extern Controller new_create_controller();

Controller controller; // global wallaby instance

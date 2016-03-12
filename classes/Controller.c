//
//  Controller.c
//  Source written by Justin Yu
//

#include "Controller.h"
#include <math.h>

static void forward(float dist, int speed);
static void backward(float dist, int speed);
static void left(int angle, float radius, int speed);
static void right(int angle, float radius, int speed);

long CMtoBEMF(float cm) {
 	return (long)(cm * 1100. / (M_PI * controller.wheel_diameter));
}

float BEMFtoCM(long ticks) {
 	return (float)(ticks * (M_PI * controller.wheel_diameter) / 1100.);
}

static void forward(float dist, int speed) {
	if(dist < 0.){
		backward(-dist, speed);
      	return;
    }

  	// Calculate the # of ticks the robot must move for each wheel
	long ticks = CMtoBEMF(dist);
	long totalLeftTicks = gmpc(controller.motor_left) + ticks;
	long totalRightTicks = gmpc(controller.motor_right) + ticks;

  	// Start motors
	motor(controller.motor_left, speed);
	motor(controller.motor_right, speed);

  	// Keep moving until both motors reach their desired # of ticks
	while(gmpc(controller.motor_left) < totalLeftTicks
          && gmpc(controller.motor_right) < totalRightTicks) {
		if (gmpc(controller.motor_left) >= totalLeftTicks)
			off(controller.motor_left);
		if (gmpc(controller.motor_right) >= totalRightTicks)
			off(controller.motor_right);
	}

	off(controller.motor_left);
  	off(controller.motor_right);
}

static void backward(float dist, int speed) {
	if(dist < 0.) {
		forward(-dist, speed);
      	return;
    }

  	// Calculate the # of ticks the robot must move for each wheel
	long ticks = CMtoBEMF(dist);
	long totalLeftTicks = gmpc(controller.motor_left) - ticks;
	long totalRightTicks = gmpc(controller.motor_right) - ticks;

  	// Start motors
	motor(controller.motor_left, -speed);
	motor(controller.motor_right, -speed);

  	// Keep moving until both motors reach their desired # of ticks
	while(gmpc(controller.motor_left) > totalLeftTicks
          && gmpc(controller.motor_right) > totalRightTicks) {
		if (gmpc(controller.motor_left) <= totalLeftTicks)
			off(controller.motor_left);
		if (gmpc(controller.motor_right) <= totalRightTicks)
			off(controller.motor_right);
	}
    off(controller.motor_left);
    off(controller.motor_right);
}

// FIX THESE

static void left(int angle, float radius, int speed) {
    int turnlspeed;
	long turnl = (CMtoBEMF(2 * (radius - controller.distance_between_wheels) * M_PI)) * (angle / 360.);
	long turnr = (CMtoBEMF(2 * (radius + controller.distance_between_wheels) * M_PI)) * (angle / 360.);
    if(turnr == 0)
		return;

    turnlspeed = round((float)turnl / (float)turnr * speed);
    msleep(30);

    if(turnr > 0)
      motor(controller.motor_right, speed);
    else
      motor(controller.motor_right, -speed);

    if(turnlspeed < 0)
        turnlspeed = -turnlspeed;
	if(turnl > 0l)
	   motor(controller.motor_left, turnlspeed);
	else
	   motor(controller.motor_left, -turnlspeed);

    turnr += gmpc(controller.motor_right);
    turnl += gmpc(controller.motor_left);

    if(turnl - gmpc(controller.motor_left) > 0l) {
        if(turnr - gmpc(controller.motor_right) > 0l){
            while((turnl > gmpc(controller.motor_left) && turnlspeed != 0) || turnr > gmpc(controller.motor_right)) {
                if(turnl < gmpc(controller.motor_left) - 10)
					off(controller.motor_left);
                if(turnr < gmpc(controller.motor_right) - 10)
					off(controller.motor_right);
            }
        } else {
            while((turnl > gmpc(controller.motor_left) && turnlspeed != 0) || turnr < gmpc(controller.motor_right)) {
                if(turnl < gmpc(controller.motor_left) - 10)
                    off(controller.motor_left);
                if(turnr > gmpc(controller.motor_right) + 10)
                    off(controller.motor_right);
            }
        }
    } else {
        if(turnr - gmpc(controller.motor_right) > 0) {
            while((turnl < gmpc(controller.motor_left) && turnlspeed != 0) || turnr > gmpc(controller.motor_right)) {
                if(turnl > gmpc(controller.motor_left) + 10)
                    off(controller.motor_left);
                if(turnr < gmpc(controller.motor_right) - 10)
                    off(controller.motor_right);
            }
        } else {
            while((turnl < gmpc(controller.motor_left) && turnlspeed != 0) || turnr < gmpc(controller.motor_right)) {
                if(turnl > gmpc(controller.motor_left) + 10)
                    off(controller.motor_left);
                if(turnr > gmpc(controller.motor_right) + 10)
                    off(controller.motor_right);
            }
        }
    }
    off(controller.motor_left);
    off(controller.motor_right);
    msleep(30);
}

static void right(int angle, float radius, int speed) {
	int turnrspeed;
	long turnl = (CMtoBEMF(2 * (radius + controller.distance_between_wheels) * M_PI)) * (angle / 360.);
	long turnr = (CMtoBEMF(2 * (radius - controller.distance_between_wheels) * M_PI)) * (angle / 360.);
    if(turnl == 0)
        return;

    turnrspeed = round((float)turnr / (float)turnl * speed);
    msleep(30);

    if(turnl > 0)
      	motor(controller.motor_left, speed);
    else
      	motor(controller.motor_left, -speed);

    if(turnrspeed < 0)
        turnrspeed = -turnrspeed;
	if(turnr > 0)
		motor(controller.motor_right, turnrspeed);
	else
		motor(controller.motor_right, -turnrspeed);

    turnl += gmpc(controller.motor_left);
    turnr += gmpc(controller.motor_right);

    if(turnr - gmpc(controller.motor_right) > 0){
        if(turnl - gmpc(controller.motor_left) > 0){
            while((turnr > gmpc(controller.motor_right) && turnrspeed != 0) || turnl > gmpc(controller.motor_left)) {
                if(turnr < gmpc(controller.motor_right) - 10)
                    off(controller.motor_right);
                if(turnl < gmpc(controller.motor_left) - 10)
                    off(controller.motor_left);
            }
        } else {
            while((turnr > gmpc(controller.motor_right) && turnrspeed != 0) || turnl < gmpc(controller.motor_left)) {
                if(turnr < gmpc(controller.motor_right) - 10)
                    off(controller.motor_right);
                if(turnl > gmpc(controller.motor_left) + 10)
                    off(controller.motor_left);
        	}
        }
    } else {
        if(turnl - gmpc(controller.motor_left) > 0l) {
            while((turnr < gmpc(controller.motor_right) && turnrspeed != 0) || turnl > gmpc(controller.motor_left)) {
                if(turnr > gmpc(controller.motor_right) + 10)
                    off(controller.motor_right);
                if(turnl < gmpc(controller.motor_left) - 10)
                    off(controller.motor_left);
            }
        } else {
            while((turnr < gmpc(controller.motor_right) && turnrspeed != 0) || turnl < gmpc(controller.motor_left)) {
                if(turnr > gmpc(controller.motor_right) + 10)
                    off(controller.motor_right);
                if(turnl > gmpc(controller.motor_left) + 10)
                    off(controller.motor_left);
            }
        }
    }
    off(controller.motor_right);
	off(controller.motor_left);
    msleep(30);
}

static void slow_servo(int port, int position, float time) {
    float increment = .01;
	float curr, start = controller.get_servo_position(port);
	float i = ((position - start) / time) * increment;
	curr = start;
	if (start > position)
	{
		while(curr > position)
		{
			controller.servo(port, curr);
			curr += i;
			msleep((long)(increment * 1000));
		}
	}
	else if (start < position)
	{
		while(curr < position)
		{
			controller.servo(port, curr);
			curr += i;
			msleep((long)(increment * 1000));
		}
	}
	controller.servo(port, position);
}

static int set_motor_left(int port) {
    if(port < 0 || port > 3) {
        return 0;
    }
    controller.motor_left = port;
    return 1;
}

static int set_motor_right(int port) {
    if(port < 0 || port > 3) {
        return 0;
    }
    controller.motor_right = port;
    return 1;
}

// Constructors

Controller new_controller(int motor_left, int motor_right,
                    int distance_between_wheels, int wheel_diameter) {
	Controller instance = {

        // Instance Variables (with no setters)
        .distance_between_wheels = distance_between_wheels,
        .wheel_diameter = wheel_diameter,

        // Setters

        .set_motor_left = &set_motor_left,
        .set_motor_right = &set_motor_right,

        // Assign method references
        .forward = &forward, .backward = &backward,
        .left = &left, .right = &right,
        .motor = &motor,
        .mav = &mav, .mtp = &mtp, .mrp = &mrp,
        .stop = &ao,
        .motor_off = &off,
        .gmpc = &gmpc,
        .clear_motor_position_counter = &cmpc,
        .gmpc = &gmpc, .cmpc = &cmpc,
        .enable_servo = &enable_servo,
        .disable_servo = &disable_servo,
        .enable_servos = &enable_servos,
        .disable_servos = &disable_servos,
        .get_servo_position = &get_servo_position,
        .servo = &set_servo_position,
        .slow_servo = &slow_servo,
        .digital = &digital,
        .analog = &analog, .analog8 = &analog8,
        .analog10 = &analog10, .analog_et = &analog_et
    };

    controller = &instance;

    // instance variables (with setters)
    if(controller.set_motor_left(motor_left) == 0)
        controller.motor_left = 0;
    if(controller.set_motor_right(motor_right) == 0)
        controller.motor_right = 0;

    return instance;
}

Controller new_create_controller() {
	Controller instance = {
        // Assign method references
        .motor = &motor,
        .mav = &mav, .mtp = &mtp, .mrp = &mrp,
        .stop = &ao,
        .motor_off = &off,
        .gmpc = &gmpc,
        .clear_motor_position_counter = &cmpc,
        .gmpc = &gmpc, .cmpc = &cmpc,
        .enable_servo = &enable_servo,
        .disable_servo = &disable_servo,
        .enable_servos = &enable_servos,
        .disable_servos = &disable_servos,
        .get_servo_position = &get_servo_position,
        .servo = &set_servo_position,
        .slow_servo = &slow_servo,
        .digital = &digital,
        .analog = &analog, .analog8 = &analog8,
        .analog10 = &analog10, .analog_et = &analog_et
    };
    controller = &instance;
    return instance;
}

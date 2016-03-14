//
//  MyClass.c
//  Source written by Justin Yu
//

#include "MyClass.h"

// custom subroutines

static void an_instance_method() {
    my_robot.controller.forward(10, 80); // tell the robot's controller to go forward 10 cm
                                          // at 80% speed
}

// constructor - create a robot

MyClass new_myclass(int a_property) {
	MyClass instance = {
        // In your constructor, you need to set every instance variable / method

        .a_property = a_property, // assign variables from the constructor
        .an_instance_method = &an_instance_method // assign to the function pointer
    };
    instance.controller = new_controller(); // instantiate your controller property
    return instance;
}

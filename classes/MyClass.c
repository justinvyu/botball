//
//  MyClass.c
//  Source written by Justin Yu
//

#include "MyClass.h"

// custom subroutines

static void an_instance_method() {
    robot.create.forward(10, 200);
}

// constructor - create a robot

MyClass new_robot(int a_property) {
    MyClass instance = {
        // In your constructor, you need to set
        // every instance variable / method

        .a_property = a_property, // assign variables from the constructor
        .an_instance_method = &an_instance_method // assign to the function pointer
    };

    // Instantiate your controller, create, etc.
    instance.controller = new_create_controller();
    instance.create = new_create();
    // instance.camera = new_camera(); // uncomment if you have a camera

    return instance;
}

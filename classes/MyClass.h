//
//  MyClass.h
//  Source written by someone
//

#include <kipr/botball.h>

// Include the other class files

#include "Controller.h"
#include "Create.h"
#include "Camera.h"

// Define a "class" for your robot

typedef struct MyClass {
    Controller controller; // refers to the wallaby controller
    Create create; // refers to your create
    // Camera camera; // uncomment if you have a camera

    // Custom properties/instance methods

    int a_property;

    // instance methods must be listed as FUNCTION POINTERS
    // that's what the little star (*) is for
    void (*an_instance_method)();

} MyClass;

extern MyClass new_robot(int a_property); // constructor

// Global robot object
MyClass robot;

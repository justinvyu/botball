//
//  MyClass.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>
#include "Controller.h"

// Define a "class" for your robot

typedef struct MyClass {
    Controller controller; // refers to the wallaby controller
    Create create; // refers to your create

    // Custom properties/instance methods

    int a_property;

    // instance methods must be listed as FUNCTION POINTERS
    // that's what the little star (*) is for
    void (*an_instance_method)();

} MyClass;

extern MyClass new_myclass(int a_property); // constructor

// Global robot object
MyClass my_robot;

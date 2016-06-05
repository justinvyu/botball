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
    int a_property;
    void (*an_instance_method)();
} MyClass;

extern MyClass new_robot(int a_property); // constructor

// Global robot object
MyClass robot;

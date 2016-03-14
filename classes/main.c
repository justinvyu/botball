#include <kipr/botball.h>

#include "MyClass.h"

int main()
{
    // instantiate your robot object
    my_robot = new_myclass(4); // pass in parameters into the constructor

    my_robot.create.connect(); // access methods from the create
                               // connect to the create

    my_robot.controller.motor(0, 80); // access methods from the controller
                                      // move motor 0 at 80% speed

    my_robot.an_instance_method(); // call your custom methods

    printf("%d", my_robot.a_property); // access custom properties of your robot
                                       // this will print: 4

    my_robot.create.disconnect();

  	return 0;
}

#include <kipr/botball.h>

#include "MyClass.h"

int main()
{
    // instantiate your global robot object
    robot = new_robot(4);

    robot.create.connect();
    robot.controller.motor(0, 80);
    robot.an_instance_method();
    printf("%d", robot.a_property);

    robot.create.disconnect();

    return 0;
}

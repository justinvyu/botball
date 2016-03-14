#include <kipr/botball.h>

#include "Scorpion.h"

int main()
{
    scorpion = new_scorpion();

    scorpion.create.connect();

    scorpion.controller.enable_servos();
    scorpion.controller.servo(BACK_SERVO, BACK_UP);
    scorpion.raise_arm();

    // scorpion.create.forward(4.5, 150);
    // scorpion.create.left(90, 0, 150);

    scorpion.controller.servo(CLAW_SERVO, CLAW_PARTIAL);
    scorpion.controller.servo(ARM_SERVO, ARM_DOWN - 400);
    msleep(500);

    scorpion.create.forward(120, 250);
    scorpion.create.left(2, 0, 100);

    scorpion.open_claw();
    scorpion.lower_arm();

    scorpion.create.forward(2, 100);

    // Get the first tribble pile

    scorpion.grab_tribbles();
    scorpion.set_arm_to_position(ARM_PARTIAL);

    scorpion.create.right(221, 0, 150);
    scorpion.controller.servo(BACK_SERVO, BACK_DOWN);
    msleep(500);

    scorpion.create.backward(30, 100);
	scorpion.create.left(23, 0, 100);
    scorpion.create.backward(26, 100); // going back, getting the box
    scorpion.create.right(6, 0, 100);
    scorpion.create.backward(4, 150);

    scorpion.controller.slow_servo(BACK_SERVO, BACK_UP, 1.5);
    scorpion.create.forward(3, 100);

    scorpion.raise_arm();
    scorpion.open_claw();
    scorpion.shake();

    // Get second tribble pile

    scorpion.create.left(16, 0, 100);
    scorpion.create.forward(36, 100);
    scorpion.lower_arm();
    scorpion.grab_tribbles();

    scorpion.create.backward(5, 150);

    scorpion.raise_arm();
    scorpion.open_claw();
    scorpion.shake();

    // Get third tribble pile

    scorpion.create.left(135, 0, 150);
    scorpion.lower_arm();
    scorpion.create.backward(10, 200);
    scorpion.grab_tribbles();

    scorpion.create.backward(20, 200);
    scorpion.raise_arm();
    scorpion.open_claw();
    scorpion.shake();

    scorpion.controller.slow_servo(BACK_SERVO, BACK_DOWN, 1.5);

  	return 0;
}

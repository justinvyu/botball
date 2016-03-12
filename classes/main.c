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

    // Get the first tribble pile

    scorpion.grab_tribbles();
    scorpion.set_arm_to_position(ARM_PARTIAL);

    scorpion.create.right(218, 0, 150);
    scorpion.controller.servo(BACK_SERVO, BACK_DOWN);
    msleep(500);

    scorpion.create.backward(30, 100);
	scorpion.create.left(25, 0, 100);
    scorpion.create.backward(27, 100); // going back, getting the box
    scorpion.create.right(10, 0, 100);
    scorpion.create.backward(2, 150);

    scorpion.controller.slow_servo(BACK_SERVO, BACK_UP, 1.5);
    scorpion.create.forward(3, 100);

    scorpion.controller.servo(ARM_SERVO, ARM_UP);
    msleep(500);
    scorpion.open_claw();
    scorpion.shake();

    scorpion.create.left(19, 0, 100);
    scorpion.create.forward(35, 100);
    scorpion.lower_arm();
    scorpion.set_claw_to_position(CLAW_PARTIAL);
    scorpion.create.forward(5, 100);
    scorpion.close_claw_slow(1.2);

    scorpion.create.backward(10, 150);

    scorpion.raise_arm();
    scorpion.open_claw();

  	return 0;
}

#include <kipr/botball.h>

// #include "Create.h"
#include "Scorpion.h"
#include "create.h"
#include "generic.h"

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

    scorpion.create.forward(124, 300);
    scorpion.open_claw();
    scorpion.lower_arm();

    // Get the first tribble pile

    scorpion.grab_tribbles();
    scorpion.raise_arm();

    scorpion.create.right(210, 0, 150);
    scorpion.controller.servo(BACK_SERVO, BACK_DOWN);
    msleep(500);
    scorpion.create.backward(30, 100);
	scorpion.create.left(26, 0, 100);
    scorpion.create.backward(30, 100); // going back, getting the box
    scorpion.create.right(10, 0, 100);
    scorpion.create.backward(2, 150);

    scorpion.controller.servo(BACK_SERVO, BACK_UP);
    msleep(2000);
    scorpion.create.forward(3, 100);
    //create_backward(5, 100);

    scorpion.controller.servo(ARM_SERVO, ARM_DOWN);
    msleep(500);
    scorpion.controller.servo(ARM_SERVO, ARM_UP);
    msleep(500);
    scorpion.controller.servo(CLAW_SERVO, CLAW_OPEN);
    msleep(2000);

    scorpion.shake_arm();

    scorpion.create.left(15, 0, 100);
    scorpion.create.forward(35, 100);
    scorpion.lower_arm();
    scorpion.set_claw_to_position(CLAW_PARTIAL);
    scorpion.create.forward(5, 100);
    scorpion.close_claw_slow(1.2);

    scorpion.create.backward(10, 150);
    scorpion.controller.servo(ARM_SERVO, ARM_DOWN);
    msleep(500);
    scorpion.controller.servo(ARM_SERVO, ARM_UP);
    msleep(500);
    scorpion.controller.servo(CLAW_SERVO, CLAW_OPEN);
    msleep(2000);

    scorpion.shake_arm();

  	return 0;
}

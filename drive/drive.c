#include "drive.h"
#include <math.h>

void drive_off() {
	off(MOT_RIGHT);
	off(MOT_LEFT);
}
void clear_all_drive(){
	clear_motor_position_counter(MOT_RIGHT);
	clear_motor_position_counter(MOT_LEFT);
}
void drive(int mL,int mR){
	motor(MOT_LEFT,mL);
	motor(MOT_RIGHT,mR);
}

long CMtoBEMF(float cm) {
 	return (long)(cm * 1100. / (PI * wheeldiameter));
}

float BEMFtoCM(long ticks) {
 	return (float)(ticks * (PI * wheeldiameter) / 1100.);
}

/* \fn void right(int degrees, int radius)
 * \brief turns right degrees degrees at int radius radius
 * \param degrees degrees forward to go
 * \param radius radius at which to turn around
 */
void right(float degrees, float radius){
		int turnrspeed;
		long turnl=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
		long turnr=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
    	if(turnl == 0l) return;
    	turnrspeed = round((float)turnr/(float)turnl*SPD);
    	msleep(30l);
    	if(turnl > 0l)
      		motor(MOT_LEFT, SPD);
    	else
      		motor(MOT_LEFT, -SPD);
    	if(turnrspeed < 0) turnrspeed = -turnrspeed;
		if(turnr > 0l)
			motor(MOT_RIGHT, turnrspeed);
		else
			motor(MOT_RIGHT, -turnrspeed);
    	turnl += gmpc(MOT_LEFT);
    	turnr += gmpc(MOT_RIGHT);
    	if(turnr - gmpc(MOT_RIGHT) > 0l){
        	if(turnl - gmpc(MOT_LEFT) > 0l){
            		while((turnr > gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl > gmpc(MOT_LEFT)){
                		if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
                		if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
            		}
        	}else{
            		while((turnr > gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl < gmpc(MOT_LEFT)){
                		if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
                		if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
            }
        }
    }else{
        if(turnl - gmpc(MOT_LEFT) > 0l){
            while((turnr < gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl > gmpc(MOT_LEFT)){
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
            }
        }else{
            while((turnr < gmpc(MOT_RIGHT) && turnrspeed != 0) || turnl < gmpc(MOT_LEFT)){
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
            }
        }
    }
    drive_off();
    msleep(30l);
}

/* \fn void left(int degrees, int radius)
 * \brief turns left degrees degrees at int radius radius
 * \param degrees degrees forward to go
 * \param radius radius at which to turn around
 */
void left(float degrees, float radius){
int turnlspeed;
	long turnl=((2*radius-ks)*CMtoBEMF*PI)*(degrees/360.);
	long turnr=((2*radius+ks)*CMtoBEMF*PI)*(degrees/360.);
    if(turnr == 0l) return;
    turnlspeed = round((float)turnl/(float)turnr*SPD);
    msleep(30l);
    if(turnr > 0l)
      motor(MOT_RIGHT, SPD);
    else
      motor(MOT_RIGHT, -SPD);
    if(turnlspeed < 0) turnlspeed = -turnlspeed;
	if(turnl > 0l)
	  motor(MOT_LEFT, turnlspeed);
	else
	  motor(MOT_LEFT, -turnlspeed);
    turnr += gmpc(MOT_RIGHT);
    turnl += gmpc(MOT_LEFT);
    if(turnl - gmpc(MOT_LEFT) > 0l){
        if(turnr - gmpc(MOT_RIGHT) > 0l){
            while((turnl > gmpc(MOT_LEFT) && turnlspeed != 0) || turnr > gmpc(MOT_RIGHT)){
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
                if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
            }
        }else{
            while((turnl > gmpc(MOT_LEFT) && turnlspeed != 0) || turnr < gmpc(MOT_RIGHT)){
                if(turnl < gmpc(MOT_LEFT) - 10l) off(MOT_LEFT);
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
            }
        }
    }else{
        if(turnr - gmpc(MOT_RIGHT) > 0l){
            while((turnl < gmpc(MOT_LEFT) && turnlspeed != 0) || turnr > gmpc(MOT_RIGHT)){
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
                if(turnr < gmpc(MOT_RIGHT) - 10l) off(MOT_RIGHT);
            }
        }else{
            while((turnl < gmpc(MOT_LEFT) && turnlspeed != 0) || turnr < gmpc(MOT_RIGHT)){
                if(turnl > gmpc(MOT_LEFT) + 10l) off(MOT_LEFT);
                if(turnr > gmpc(MOT_RIGHT) + 10l) off(MOT_RIGHT);
            }
        }
    }
    drive_off();
    msleep(30l);
}

void forward(float distance) {
	if(distance < 0.){
		backward(-distance);
      	return;
    }

  	// Calculate the # of ticks the robot must move for each wheel
	long ticks = CMtoBEMF(distance);
	long totalLeftTicks = get_motor_position_counter(MOT_LEFT) + ticks;
	long totalRightTicks = get_motor_position_counter(MOT_RIGHT) + ticks;

  	// Start motors
	motor(MOT_LEFT, SPDl);
	motor(MOT_RIGHT, SPDr);

  	// Keep moving until both motors reach their desired # of ticks
	while(get_motor_position_counter(MOT_LEFT) < totalLeftTicks
          && get_motor_position_counter(MOT_RIGHT) < totalRightTicks) {
		if (get_motor_position_counter(MOT_LEFT) >= totalLeftTicks)
			off(MOT_LEFT);
		if (get_motor_position_counter(MOT_RIGHT) >= totalRightTicks)
			off(MOT_RIGHT);
	}

	off(MOT_LEFT);
  	off(MOT_RIGHT);
}

void backward(float distance){
	if(distance < 0.){
		forward(-distance);
      	return;
    }

  	// Calculate the # of ticks the robot must move for each wheel
	long ticks = CMtoBEMF(distance);
	long totalLeftTicks = get_motor_position_counter(MOT_LEFT) - ticks;
	long totalRightTicks = get_motor_position_counter(MOT_RIGHT) - ticks;

  	// Start motors
	motor(MOT_LEFT, -SPDl);
	motor(MOT_RIGHT, -SPDr);

  	// Keep moving until both motors reach their desired # of ticks
	while(get_motor_position_counter(MOT_LEFT) > totalLeftTicks
          && get_motor_position_counter(MOT_RIGHT) > totalRightTicks) {
		if (get_motor_position_counter(MOT_LEFT) <= totalLeftTicks)
			off(MOT_LEFT);
		if (get_motor_position_counter(MOT_RIGHT) <= totalRightTicks)
			off(MOT_RIGHT);
	}

	off(MOT_LEFT);
  	off(MOT_RIGHT);
}

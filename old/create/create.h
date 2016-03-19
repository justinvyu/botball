//
//  create.h
//  Source written by Justin Yu
//

#include <kipr/botball.h>

#ifndef _CREATE_H_
#define _CREATE_H_

void create_write_int(int value);

float CTICKtoCM(long tick);
long CMtoCTICK(float cm);

void clear_create_distance();
void clear_create_angle();

void create_left(int angle, float radius, int speed);
void create_right(int angle, float radius, int speed);
void create_forward(float dist, int speed);
void create_backward(float dist, int speed);

void create_forward_until_bump(int speed);

void create_send();
void create_receive();
void create_block();

#endif

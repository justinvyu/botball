#ifndef _FINALCREATE
#define _FINALCREATE

#define WHEEL_DROP 1
#define CLIFF 10
#define BUMP 5
#define LEFT_BUMP 6
#define RIGHT_BUMP 7
#define BUTTON_ADVANCED 16
#define BUTTON_PLAY 17
#define SEN_0 18

// enum CreateEvent {
// 	WheelDrop = 1,
// 	Bump = 6,
// 	LeftBump = 6,
// 	RightBump = 7,
// 	Cliff = 10,
// 	ButtonAdvanced = 16,
// 	ButtonPlay = 17,
// }

#define get_high_byte2(a) ((a)>>8)
#define get_low_byte2(a) ((a)&255)

#define create_write_int(integer) create_write_byte(get_high_byte2(integer));create_write_byte(get_low_byte2(integer))

void create_wait_time(int time)
{
	create_write_byte(155);
	create_write_byte(time);
}

void create_wait_dist(int dist)//dist is in mm
{
	create_write_byte(156);
	create_write_int(dist);
}

void create_wait_angle(int angle) {
	create_write_byte(157);
	create_write_int(angle);
}

void create_wait_event(enum CreateEvent event) {
	create_write_byte(158);
	create_write_byte(event);
}

void create_drive_direct_dist(int r_speed, int l_speed, int dist) {
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_dist(dist);
}

void create_drive_direct_left(int r_speed, int l_speed, int angle) {
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_angle(angle);
}

void create_drive_direct_right(int r_speed, int l_speed, int angle) {
	create_write_byte(145);
	create_write_int(r_speed);
	create_write_int(l_speed);
	create_wait_angle(-angle);
}

void create_right(int angle, int radius, int speed) {
	create_write_byte(137);
	create_write_int(speed);
	if (radius == 0){
		create_write_int(-1);
	}else{
		create_write_int(-radius);
	}
	create_wait_angle(-angle);
}

void create_left(int angle, int radius, int speed) {
	create_write_byte(137);
	create_write_int(speed);
	if (radius == 0) {
		create_write_int(1);
	} else {
		create_write_int(radius);
	}
	create_wait_angle(angle);
}

void create_forward(int dist, int speed) {
	create_write_byte(145);
	create_write_int(speed);
	create_write_int(speed);
	create_wait_dist(dist);
}

void create_backward(int dist, int speed ) {
	create_write_byte(145);
	create_write_int(-speed);
	create_write_int(-speed);
	create_wait_dist(-dist);
}

void create_block() {
	create_stop();
	create_send();
	create_recieve();
}

// MISC. Methods

void create_crash() {
	create_write_byte(7);
}

void output_sen_0() {
	create_write_byte(147);
	create_write_byte((0*1)+(0*2)+(1*4));
}

void stop_output() {
	create_write_byte(147);
	create_write_byte(0);
}

void create_send() {
	create_write_byte(142);
	create_write_byte(35);
}
void create_recieve() {
	char buffer[1];
	char *bptr = buffer;
	create_read_block(bptr,1);
}

void create_motors(int speed) {
	create_write_byte(144);
	create_write_byte(speed);
	create_write_byte(speed);
	create_write_byte(speed);
}

#endif

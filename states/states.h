
//
//  states.h
//
//  by Justin Yu
//

// Global state variable
int currstate;

// Shortcut Functions
#define state(specified_state) if (curr_state == specified_state)
#define next(new_state) curr_state = new_state
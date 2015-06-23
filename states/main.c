
//
//  main.c
//
//  by Justin Yu
//

#include "states.h"

#define s_START 0
#define s_ACTION_1 1
#define s_ACTION_2 2

#define s_END 1337

int main() {
    
    // Any initializing code
    
    next(s_START); // curr_state is now s_START
    while( curr_state != s_END ) {
        state(s_START) {
            // actions to perform in the s_START stage
            next(s_ACTION_1); // move on to next action
        }
        state(s_ACTION_1) {
            next(s_ACTION_2);
        }
        state(s_ACTION_2) {
            next(s_END);
        }
    }
    
    // Any terminating code
    
}
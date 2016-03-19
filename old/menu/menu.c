#include "generic.h"
#include "menu.h"

/**
 * Waits for user touch and sets the current state to the mode selected.	
 * @param menu_size The number of menu items [the number of states]
 */
void Get_Mode(int menu_size) {
	MENU_SIZE = menu_size;
	currstate = menu[options(menu_size)].snum;
}

int selection_list(int length) {
	int current = DEFAULT_OPTION;
	int counter = 1;
	int oldcurrent = DEFAULT_OPTION;
	while(1) {
		if(a_button()) {
			while(a_button()) msleep(1);
			return current;
		}
		if(c_button()) {
			while(c_button()) msleep(1);
			oldcurrent = current;
			current--;
			counter = 1;
			if(current < 0) current = length - 1;
		}
		if(b_button()) {
			while(b_button()) msleep(1);
			oldcurrent = current;
			current++;
			counter = 1;
			if (current >= length) current = 0;
		}
		if(counter == 1) {
			display_printf(0, oldcurrent + 1, " ");
			display_printf(0, current + 1, "*");
			counter = 0;
		}
	}
}

/**
 * Initializes the menu and returns the result to the function Get_Mode
 * After the user presses a button to select their state, Get_Mode will set the state
 * the state selected.
 * 
 * @return           Returns the option number, in terms of array index.
 *                   The parent 
 */
int options(int menu_size) {
	display_clear();
	msleep(10);
	int result;
	display_printf(0,0,"A Accept | B down | C up\n");
	result = selection_list(draw_screen(menu_size));
	display_clear();
	return result;
}

/**
 * Prints out the states and their descriptions.
 * This function returns its parameter to print out the menu items along the way.
 * 
 * @return           Returns the number of menu items
 */
int draw_screen() {
	int i;
	for(i = 0; i < MENU_SIZE; i++){
		display_printf(0, i + 1, "  %s", menu[i].name);
	}
	return MENU_SIZE;
}

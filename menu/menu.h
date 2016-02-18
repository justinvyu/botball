#define DEFAULT_OPTION 0

//#define Get_Mode(menu_size) currstate = menu[options(menu_size)].snum

struct menuitem {
	int snum; // the state's value
	char* name; // the state's label / name
};
extern struct menuitem menu[];

int MENU_SIZE;

int selection_list(int length);
int options(); 
int draw_screen();
void Get_Mode(int menu_size);

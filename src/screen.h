#ifndef __screen
#define __screen

#include "ncurses.h"
#include "file.h"

int start_display();
int main_loop();
void print_file(File *f);

#endif //__screen

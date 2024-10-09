#include "screen.h"
#include "file.h"
#include <locale.h>
#include <ncurses.h>


WINDOW * main_display;
int start_display() {
    setlocale(LC_ALL, "");
    main_display = initscr();
    keypad(stdscr, TRUE);
    cbreak();   
    keypad(main_display, TRUE);
    noecho();
    main_loop();

	return 0;
}

void print_file(File *f) {
    clear();
    printw("length: %d, cursor: %d %d \n", f->line_count, f->x_cursor, f->y_cursor);
    for (int i = 0; i < f->line_count; ++i) {
        if (f->line[i].chr)
        printw("%d |%s\n",i, f->line[i].chr);
    }
}

int main_loop() {
File f = {
    .y_cursor = 0,
    .x_cursor = 0,
    .line = 0,
    .line_count = 0
};

create_line(&f);
    while (1) {
        print_file(&f);
        move(f.y_cursor + 1, f.x_cursor + 3);
        int ch = getch();
        switch (ch) {
            case 27: 
                endwin();
                return 0;
            case KEY_BACKSPACE:
                delete_in_file(&f);
                break;
            case KEY_UP:
                move_cursor_up(&f);
                break;
            case KEY_DOWN:
                move_cursor_down(&f);
                break;
            case KEY_LEFT:
                move_cursor_left(&f);
                break;
            case KEY_RIGHT:
                move_cursor_right(&f);
                break;
            case 10:
                create_line(&f);
                break;
            default: 
                insert_in_file(ch, &f);
                break;
        }
        refresh();
    }
}

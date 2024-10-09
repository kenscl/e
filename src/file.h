#ifndef __file
#define __file
#include <stddef.h>
#include <sys/types.h>

typedef struct {
    char *chr;
    size_t size;
} Line;

typedef struct {
    Line *line;
    size_t line_count;
    uint x_cursor;
    uint y_cursor;
} File;

void create_line(File *file);
void insert_in_file(char c, File *file);
void delete_line(File *file);
void delete_in_file(File *file);
void move_cursor_up(File *file);
void move_cursor_down(File *file);
void move_cursor_left(File *file);
void move_cursor_right(File *file);
#endif //__file

#include "file.h"
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

void create_line(File *file) {
    uint pos = file->y_cursor;

    Line *new_line = (Line*)malloc((file->line_count + 1) * sizeof(Line));
    if (file->line_count == 0) {
        new_line[pos].chr = (char*)malloc(sizeof(char));
        *new_line[pos].chr = '\0';
        new_line[pos].size = 0;
        file->line = new_line;
        file->line_count = 1;
        file->y_cursor = 0;
        file->x_cursor = 0;
        return;
    }
    if (pos == file->line_count - 1) {
        memcpy (new_line, file->line, file->line_count * sizeof(Line));
        new_line[pos+1].chr = (char*)malloc(sizeof(char));
        *new_line[pos+1].chr = '\0';
        new_line[pos+1].size = 0;
        free (file->line);
        file->line = new_line;
        file->line_count++;
        file->y_cursor++;
        file->x_cursor = 0;
        return;
    }
    else {
        memcpy (new_line, file->line, pos * sizeof(Line));
        memcpy (new_line + pos + 1, file->line + pos, (file->line_count - pos) * sizeof(Line));
        new_line[pos+1].chr = (char*)malloc(sizeof(char));
        *new_line[pos+1].chr = '\0';
        new_line[pos+1].size = 0;
        free (file->line);
        file->line = new_line;
        file->line_count++;
        file->y_cursor++;
        file->x_cursor = 0;
        return;
    }
}

void insert_in_file(char c, File *file) 
{
    Line *line = &file->line[file->y_cursor];
    char *new_line = (char*)calloc((line->size + 2), sizeof(char));
    if (file->x_cursor == 0) 
    {
        memcpy (new_line + 1, line->chr, (line->size + 1) * sizeof(char));
        new_line[0] = c;
        free (line->chr);
        line->chr = new_line;
        line->size++;
        file->x_cursor++;
        return;
    }
    else
    {
        memcpy (new_line, line->chr, file->x_cursor * sizeof(char));
        memcpy (new_line + file->x_cursor + 1 , line->chr + file->x_cursor, (line->size - file->x_cursor) * sizeof(char));
        new_line[file->x_cursor] = c;
        free (line->chr);
        line->chr = new_line;
        line->size++;
        file->x_cursor++;
        return;
    }
}


void delete_line(File *file) {
    size_t len = file->y_cursor;
    if (file->line_count <= 1) return;

    Line* new_line = (Line*) malloc ((file->line_count - 1) * sizeof(Line));
    memcpy(new_line, file->line, len * sizeof(Line));
    memcpy(&new_line[len], &file->line[len + 1], (file->line_count - len - 1) * sizeof(Line));
    free (file->line);
    file->line = new_line;
    file->line_count--;
    file->y_cursor--;
    file->x_cursor = file->line[file->y_cursor].size;
    return;
}

void delete_in_file(File *file) {
    if (file->y_cursor > file->line_count) return;
    size_t len = file->line[file->y_cursor].size;
    if (len == 0) 
    {
        delete_line(file);
        return;
    }
    if (file->x_cursor > len) return;

    char *line = file->line[file->y_cursor].chr;

    char *new_line = (char*)malloc(len * sizeof(char));
    memcpy(&line[file->x_cursor], &line[file->x_cursor+1], (len - file->x_cursor) * sizeof(char));
    memcpy(new_line, line, len * sizeof(char));
    new_line[len-1] = '\0';

    free(file->line[file->y_cursor].chr);
    file->line[file->y_cursor].chr = new_line;
    file->line[file->y_cursor].size--;
    file->x_cursor--;
}

void move_cursor_up(File *file) {
    if (file->y_cursor > 0) {
        file->y_cursor--;
        if (file->x_cursor > file->line[file->y_cursor].size) {
            file->x_cursor = file->line[file->y_cursor].size;
        }
    }
}

void move_cursor_down(File *file) {
    if (file->y_cursor <= file->line_count) {
        file->y_cursor++;
        if (file->x_cursor > file->line[file->y_cursor].size) {
            file->x_cursor = file->line[file->y_cursor].size;
        }
    }
}

void move_cursor_left(File *file) {
    if (file->x_cursor == 0) {
        move_cursor_up(file);
        file->x_cursor = file->line[file->y_cursor].size;
    }
    else {
        file->x_cursor--;
    }
}

void move_cursor_right(File *file) {
    if (file->x_cursor == file->line[file->y_cursor].size) {
        move_cursor_down(file);
        file->x_cursor = 0;
    }
    else {
        file->x_cursor++;
    }
}

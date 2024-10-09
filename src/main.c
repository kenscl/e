#include <stdio.h>
#include "screen.h"
#include "file.h"


void printf_file(File *f) {
    //clear();
    printf("length: %d \n", f->line_count);
    for (int i = 0; i < f->line_count; ++i) {
        printf("%d |%s\n",i, f->line[i].chr);
    }
}

int main (int)
{
    start_display();
}


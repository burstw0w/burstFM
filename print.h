#ifndef PRINT_H
#define PRINT_H
#include "files.h"
#include <ncurses.h>

int print_directories(WINDOW *win, int i, FileInfo *lista, int selected);
void draw_ui(WINDOW *win, int w, int h);

#endif // !


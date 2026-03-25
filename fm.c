#include <stdio.h>
#include <stdlib.h>
#include "files.h"
#include "print.h"
#include "input.h"

int main() {

    int w = 80;
    int h = 24;
    int mid = w/2;
    int selected = 0;
    initscr();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    FileInfo *file_list = NULL;
    int file_count;
//mvwprintw(win , 1, 1, "Burst's Utterly Useless File Manager");
//    mvwhline(win, 2, 1, ACS_HLINE, w-2);
//    mvwprintw(win, 3, 1, "FILE NAME");
//    mvwprintw(win, 3, w - 5, "SIZE");
//    mvwvline(win, 3, mid, ACS_VLINE, h-4);
//    mvwhline(win, 4, 1, ACS_HLINE, w-2);
    file_count = load_directory(".", &file_list);

    if (file_count < 0) {
        perror("Failed to load directory");
        return 1;
    }
    WINDOW *win = newwin(file_count+6, w, 0, 0);
    keypad(win, TRUE);
    draw_ui(win, w, file_count+6);


    print_directories(win, file_count, file_list, selected);
    refresh();
    wrefresh(win);
    move_cursor(&win, &file_list, file_count, selected, ".");

    free(file_list);
    getch();    
    endwin();
    return 0;
}

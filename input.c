#include "input.h"
#include "files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int move_cursor(WINDOW **win, FileInfo **file_list, int file_count, int selected, const char *initial_path){
  char current_path[512];
  strncpy(current_path, initial_path, sizeof(current_path)-1);
  current_path[sizeof(current_path)-1] = '\0';

  int ch;
  int rows, cols;
  getmaxyx(*win, rows, cols);

  while((ch=wgetch(*win))!= 'q'){
    switch(ch){
      case KEY_UP:
        if(selected>0) selected--;
        break;
      case KEY_DOWN:
        if(selected < file_count-1) selected++;
        break;
      case '\n':
        if((*file_list)[selected].is_directory){
          char next_path[512];
          snprintf(next_path, sizeof(next_path), "%s/%s", current_path, (*file_list)[selected].name);
          strncpy(current_path, next_path, sizeof(current_path)-1);
          free(*file_list);
          file_count = load_directory(next_path, file_list);
          delwin(*win);
          *win = newwin(file_count + 6, cols, 0, 0);
          keypad(*win, TRUE);
          getmaxyx(*win, rows, cols);
          clear();
          refresh();
          selected = 0;
        }
    }
    werase(*win);
    draw_ui(*win, cols, rows);
    print_directories(*win, file_count, *file_list, selected);
    wrefresh(*win);
  }

  return selected;
}


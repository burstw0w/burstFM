#include "print.h"
#include "files.h"
#include <stdio.h>
#include <string.h>

int print_directories(WINDOW *win, int i, FileInfo *lista, int selected){
  FileInfo currentFile;
  int color, rows, cols;
  char size_str[20];
  getmaxyx(win, rows, cols);

  for(int j=0; j<i; j++){
        currentFile = lista[j];
        if(currentFile.is_directory == 0){
          color = 2;
        }else{
          color = 1;
        }
        if (j == selected){
          wattron(win, A_REVERSE);
        }
        wattron(win, COLOR_PAIR(color));
        mvwprintw(win, 5+j, 1, currentFile.name);
        currentFile.size >= 1048576 ? sprintf(size_str, "%.2f MB", currentFile.size / 1048576.0) : (currentFile.size >= 1024 ? sprintf(size_str, "%.2f KB", currentFile.size / 1024.0) : sprintf(size_str, "%ld bytes", currentFile.size));
        //sprintf(size_str, "%ld bytes", currentFile.size);
        mvwprintw(win, 5+j, cols - strlen(size_str) - 1, "%s", size_str);
        wattroff(win, COLOR_PAIR(color));
        if(j == selected){
          wattroff(win, A_REVERSE);
        }
  } 
}

void draw_ui(WINDOW *win, int w, int h){
  int mid = w / 2;
  box(win, 0, 0);
  mvwprintw(win, 1, 1, "Burst File Manager");
  mvwhline(win, 2, 1, ACS_HLINE, w-2);
  mvwprintw(win, 3, 1, "FILE NAME");
  mvwprintw(win, 3, w - 5, "SIZE");
  mvwvline(win, 3, mid, ACS_VLINE, h-4);
  mvwhline(win, 4, 1, ACS_HLINE, w-2);
}

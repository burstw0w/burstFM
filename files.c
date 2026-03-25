#include "files.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_directory(const char *path, FileInfo **files) {
  char full_path[512];
  DIR *dir = opendir(path);
  if (!dir) return -1;

  struct dirent *entry;
  struct stat st;
  int count = 0;

  *files = malloc(sizeof(FileInfo) * 1000);

  while ((entry = readdir(dir)) != NULL) {
    if (count >= 1000) break;
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
    if (stat(full_path, &st) == -1) {      
      perror("stat");
      continue;
    }

    FileInfo currentFile;

    strncpy(currentFile.name, entry->d_name, sizeof(currentFile.name) -1);
    currentFile.name[sizeof(currentFile.name) -1] = '\0';

    currentFile.size = st.st_size;
    currentFile.permissions = st.st_mode;
    currentFile.is_directory = S_ISDIR(st.st_mode);
    
    (*files)[count]= currentFile;

    count++;
  }

  closedir(dir);
  return count;
}

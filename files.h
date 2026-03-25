#ifndef FILES_H
#define FILES_H
#include <sys/types.h>
#include <sys/stat.h>

typedef struct{
  char name[256];
  off_t size;
  mode_t permissions;
  int is_directory;
} FileInfo;

int load_directory(const char *path, FileInfo **files);

#endif // !FILES_H

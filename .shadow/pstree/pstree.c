#include <stdio.h>
#include <assert.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  assert(!argv[argc]);
  FILE *fp = NULL;
  
  DIR *dir;
  struct dirent *entry;
  
  dir = opendir("/proc/");
  if(dir == NULL){
    perror("opendir failed");
    return 1;
  }
  while((entry = readdir(dir)) != NULL){
    printf("%s\n",entry->d_name);
  }
  closedir(dir);

  return 0;
}

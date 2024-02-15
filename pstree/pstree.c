#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int getps(){
  FILE *fp = NULL;
  
  DIR *dir;
  struct dirent *entry;
  
  dir = opendir("/proc/");
  if(dir == NULL){
    perror("opendir failed");
    return 1;
  }
  while((entry = readdir(dir)) != NULL){
    char* dname = entry->d_name;
    printf("%s  ",dname);
    if(dname[0]<=0 && dname[0]>9)
	printf("test char: %c",dname[0]);
	break;
    char filename[40] ;
    sprintf(filename , "%s%s%s","/proc/",dname,"/stat");
    printf("filename: %s\n",filename);
    FILE *fp = fopen(filename,"r");
    if(fp){
	char stat_txt[100];
	int pid,ppid;
	char comm[40];
	char state;
	char remind_txt[100];
	fgets(stat_txt,100,fp); 
	sscanf(stat_txt,"%d %s %c %d %s",&pid,comm,&state,&ppid,remind_txt);
	printf("pid: %d, comm: %s, stat: %c, ppid: %d",pid,comm,state,ppid);
	fclose(fp);
    }else{
	printf("open file %s error!!!",filename);
    }
  }
  closedir(dir);


  return 0;
}


int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    assert(argv[i]);
    printf("argv[%d] = %s\n", i, argv[i]);
    if(!strcmp(argv[i], "-p") || !strcmp(argv[i],"--show-pids"))
    {
	getps();
    }
    else if(!strcmp(argv[i],"-V") || !strcmp(argv[i],"--version"))
    {
	printf("print ps_version");
    }
    else if(!strcmp(argv[i],"-n") || !strcmp(argv[i],"--numeric-sort"))
    {
	printf("print ps");
    }
    else{
	printf("your input %s is error!!!fuck",argv[i]);
    }
    assert(!argv[argc]);
    }
  return 0;
}



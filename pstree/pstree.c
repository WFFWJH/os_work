#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>


int getps();

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
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



int getps(){
  FILE *fp = NULL;
  
  DIR *dir;
  struct dirent *entry;
  struct pid_info {
	int pid;
	int ppid;
	char comm[40];
	char state;
  };	
  
  dir = opendir("/proc/");
  if(dir == NULL){
    perror("opendir failed");
    return 1;
  }

  int pid_num = 0;
  char* dname_arr[1000];
  while((entry = readdir(dir)) != NULL){
    char* dname = entry->d_name;
    if(dname[0] > 47 && dname[0] < 58 ){
	dname_arr[pid_num] = dname;
        pid_num++;
    }else{
    }
  }
  printf("\n\npid_num:%d \n",pid_num);
  assert(pid_num);


  struct pid_info pids_arr[pid_num]; 
  for( int i = 0;i < pid_num; i++ ){
    char* dname = dname_arr[i];
    char filename[40] ;
    sprintf(filename , "%s%s%s","/proc/",dname,"/stat");
    printf("filename: %s\n",filename);
    FILE *fp = fopen(filename,"r");
    if(fp){

	char stat_txt[100];
	char remind_txt[100];
	fgets(stat_txt,100,fp); 

	sscanf(stat_txt,"%d %s %c %d %s",&pids_arr[i].pid,pids_arr[i].comm,\
			&pids_arr[i].state,&pids_arr[i].ppid,remind_txt);

//printf("pid: %d, comm: %s, stat: %c, ppid: %d\n",pids_arr[i].pid,pids_arr[i].comm,pids_arr[i].state,pids_arr[i].ppid,id,comm,state,ppid);

	fclose(fp);
    }else{
	printf("open file %s error!!!    \n",filename);
    }
  }
  closedir(dir);

  return 0;
}


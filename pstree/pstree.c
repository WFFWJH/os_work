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
	struct pid_info *first_child;
	struct pid_info *next_sibling;
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
    }
  }
  printf("\n\npid_num:%d \n",pid_num);
  assert(pid_num);


  struct pid_info pids_arr[pid_num+1]; 

// for pid == 0

  pids_arr[0].pid=0;
  pids_arr[0].ppid=0;
  strcpy(pids_arr[0].comm,"root");
//  *pids_arr[0].comm="root";
  pids_arr[0].state='S';
  pids_arr[0].first_child=NULL;
  pids_arr[0].next_sibling=NULL;

  for( int i = 0;i < pid_num; i++ )
  {
    char* dname = dname_arr[i];
    char filename[40] ;
    sprintf(filename , "%s%s%s","/proc/",dname,"/stat");
//    printf("filename: %s\n",filename);
    FILE *fp = fopen(filename,"r");
    if(fp){

	char stat_txt[100];
	char remind_txt[100];
	fgets(stat_txt,100,fp); 

	sscanf(stat_txt,"%d %s %c %d %s",&pids_arr[i+1].pid,pids_arr[i+1].comm,\
			&pids_arr[i+1].state,&pids_arr[i+1].ppid,remind_txt);

	pids_arr[i+1].first_child=NULL;
	pids_arr[i+1].next_sibling=NULL;
//	printf("pid: %d, comm: %s, stat: %c, ppid: %d\n",pids_arr[i].pid,pids_arr[i].comm,pids_arr[i].state,pids_arr[i].ppid);

	fclose(fp);
	
    }else{
	printf("open file %s error!!!    \n",filename);
    }
  }
  
  closedir(dir);

  void addsibling(struct pid_info *brother, struct pid_info *litter)
  {
	  if(brother->next_sibling==NULL)
		  brother->next_sibling=litter;
	  else{
		  addsibling(brother->next_sibling,litter);
	  }
  }

  void addchild(struct pid_info *parent, struct pid_info *child)
  {
	  if(parent->first_child==NULL) 
		  parent->first_child = child;
	  else{
		 addsibling(parent->first_child,child);
	  }
  }
  

printf("Begin build tree, those are %d pids.\n", pid_num);

for( int i = 0;i < pid_num; i++ ){
	  
  	for( int j = 1;j < pid_num; j++ ){
		if(pids_arr[j].ppid == pids_arr[i].pid)
		{
			addchild(&pids_arr[i],&pids_arr[j]);	
		}
	}
}

printf("build tree over! all %d pids!", pid_num);
  // Print part (preorder Traversal)
 
for( int i = 0;i < pid_num; i++ ){
	printf("the %d pid in the pid_arr is %s :",i,pids_arr[i].comm);
	printf("pid: %d, comm: %s, stat: %c, ppid: %d\n",pids_arr[i].pid,pids_arr[i].comm,pids_arr[i].state,pids_arr[i].ppid);
	if(pids_arr[i].first_child){
		if(pids_arr[i].next_sibling){
		       	printf("the  left is %s , the right is %s \n",pids_arr[i].first_child->comm,pids_arr[i].next_sibling->comm);
		}else{	
			printf(" the  left is %s , the %d pid's right is NULL\n",pids_arr[i].first_child->comm,i);
		} 
	}else{
		if(pids_arr[i].next_sibling){
		       	printf("the  left is NULL , the right is %s \n",pids_arr[i].next_sibling->comm);
		}else{	
			printf(" the  left is NULL , the  right is NULL\n");
		}
	}
}
  
void print_preorder(struct pid_info * tree , int space_num)
 {

	for(int i=0;i<space_num;i++){
		printf(" -- ");
	}
	printf("%s",tree->comm);
 	printf("\n|");
	while(tree->first_child)
	{
		print_preorder(tree->first_child,space_num+1);
		break;
	}
	 

	while(tree->next_sibling)
	{
	 	print_preorder(tree->next_sibling,space_num);
		break;
	}
 }

 print_preorder(&pids_arr[0],0);
 return 0;

}


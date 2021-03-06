#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

pthread_t tid[100];
char old[100], new[100],drit[100];

const char *getExt(const char *fName) {
  int j=0; char *dot = strrchr(fName, '.');
  if(!dot || dot == fName) return "Unknown";
  while(dot[j]) { dot[j]=tolower(dot[j]); j++; }
  return dot + 1;
}

int isFile(char *path){
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

void *cat(void *arg){
  char fileN[50],ext[10],oldP[100],newP[100],dirE[100];
  strcpy(fileN,(char *)arg);
  sprintf(oldP,"%s%s",old,fileN); 

  if(isFile(oldP)) {
    strcpy(ext,getExt(fileN)); 

    sprintf(dirE,"%s%s",drit,ext);
    DIR* dir = opendir(dirE);
    if(dir==0) {
      mkdir(dirE,0777); 
    }

    sprintf(newP,"%s%s/%s",new,ext,fileN);
    rename(oldP,newP);
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  int x,err; char file[50];

  if(strcmp(argv[1],"-f")==0) {
    int n=0; strcpy(old,""); strcpy(new,""); strcpy(drit,""); 
    while(n != (argc-2)) { 
      err=pthread_create(&tid[n],NULL,&cat,(void *)argv[n+2]);
      n++;
    }
    n=0; 
    while(n != (argc-2)) {
       pthread_join(tid[n],NULL);
       n++;
    }
   exit(0);
  }

  else if(strcmp(argv[1],"-d")==0) {
    DIR* dir = opendir(argv[2]); 
    struct dirent *d; int n=0;
    sprintf(old,"%s/",argv[2]);  strcpy(new,""); strcpy(drit,"");
    while((d = readdir(dir))!=NULL) { 
      err=pthread_create(&tid[n],NULL,&cat,(void *)d->d_name);
      n++;
    }
    
    while(n) { 
       pthread_join(tid[n-1],NULL);
       n--;
    }
   exit(0);
  }

  else if(strcmp(argv[1],"*")==0) {
    getcwd(old,sizeof(old));
    chdir("..");
    DIR* dir = opendir(old);
    struct dirent *d; int n=0;
    sprintf(old,"%s/",old);  strcpy(new,old); strcpy(drit,old);
    while((d = readdir(dir))!=NULL) { 
      err=pthread_create(&tid[n],NULL,&cat,(void *)d->d_name);
      n++;
    }
    
    while(n) { 
       pthread_join(tid[n-1],NULL);
       n--;
    }
   exit(0);
  }

  return 0;
}

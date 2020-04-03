#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

pthread_t tid[3];
int n; char *arr[100];

const char *getExt(const char *fName) {
  char *dot = strrchr(fName, '.');
  if(!dot || dot == fName) return "Unknown";
  int j=0; while(dot[j]) {
    dot[j]=tolower(dot[j]); j++;}
  return dot + 1;
}

void *cat(void *arg){
  pthread_t id = pthread_self();
  int i; char ext[10],cwd[100],oldD[100],newD[100];

  if(pthread_equal(id,tid[0])) {
    for(i=0; i<n; i++) {
      strcpy(ext,getExt(arr[i]));
      DIR* dir = opendir(ext);
      if(dir==0) {
        mkdir(ext,0777);
      }
      sprintf(newD,"%s/%s",ext,arr[i]);
      rename(arr[i],newD);
    }
  }

  else if(pthread_equal(id,tid[1])) {
    DIR* dir = opendir(arr[0]); 
    struct dirent *d;
    while((d = readdir(dir))!=NULL) {
      sprintf(oldD,"%s/%s",arr[0],d->d_name);
      strcpy(ext,getExt(d->d_name));
      DIR* dir = opendir(ext);
      if(dir==0) {
        mkdir(ext,0777);
      }
      sprintf(newD,"%s/%s",ext,d->d_name);
      rename(oldD,newD);
    }
  }

  else if(pthread_equal(id,tid[2])) {
    getcwd(cwd,sizeof(cwd));
    chdir("..");
    DIR* dir = opendir(cwd);
    struct dirent *d;
    while((d = readdir(dir))!=NULL) {
      strcpy(ext,getExt(d->d_name));
      chdir(cwd); DIR* dir = opendir(ext);
      if(dir==0) {
        mkdir(ext,0777);
      }
      sprintf(newD,"%s/%s",ext,d->d_name);
      rename(d->d_name,newD); chdir("..");
    }
  }
  return NULL;
}


int main(int argc, char *argv[]) {

  n=argc-2; int x;
  *arr=(char *)malloc(n*sizeof(char));
  for(x=0; x<n; x++) strcpy(arr[x],argv[x+2]);

  int err;
  if(strcmp(argv[1],"-f")==0) err=pthread_create(&tid[0],NULL,&cat,NULL);

  else if(strcmp(argv[1],"-d")==0) err=pthread_create(&tid[1],NULL,&cat,NULL);

  else if(strcmp(argv[1],"*")==0) err=pthread_create(&tid[2],NULL,&cat,NULL);

  if(err!=0) printf("Failure: [%s]\n",strerror(err));

  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);
  pthread_join(tid[2],NULL);
  exit(0);
  return 0;
}

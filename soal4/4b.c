#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

unsigned long long total[10][10];
pthread_t thread[500];
int status;
int (*hasil) [10];

void *factorial(void *num){
	key_t key = 8808;
   	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
   	hasil = shmat(shmid, 0, 0);
	
	if(shmid<0)
	{
		perror("shmget");
		exit(1)
	)
	
	int h,i,j;
	long long ans = 0;
	//int fak = *((int *)num);
	pthread_t id = pthread_self();
	for (i = 0; i <= 3; i++){
		for(j=0; j<=4; j++){
			jumlah = hasil[i][j];
			for(k=0;k<=jumlah;k++){			
				ans = ans + i;
				total[i][j] = ans;
	}
	while (!pthread_equal(id, thread[status]));
	printf("%lld\n", total[i][j]);
	status++;
}

int main ()
{	
	key_t key = 8808;
	int shmid = shmget (key, sizeof(int[10][10]), IPC_CREAT | 0666);
	hasil = shmat(shmid,0,0);
	int i;
	int j;

    printf("Hasil perkalian matriks: \n");
    for(i = 0; i < 4; i++){
        for(j = 0; j < 5; j++){
            printf("%d\t", hasil[i][j]);
        }
        printf("\n");
    }

    printf ("\nHasil sum:\n");
	//...
    return 0;
}

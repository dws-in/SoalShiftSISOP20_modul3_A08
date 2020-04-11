#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

void *addition(void* arg) 
{ 
    int *n = (int *)arg;
    int a = *n;
    int result = 0;

    for(int i=1;i<=a;i++){
        result += i;
    }
    int *res = (int*)malloc(sizeof(int));
    *res = result;
}

int main(){
    		// shared memory tempelate
		key_t key=1234;
		int shmid = shmget(key, sizeof (int[20]), IPC_CREAT | 0666);
		int (*C)[4][5];
		C = shmat(shmid,0,0);
	
	// ini pokonya cuma copas yang dari 4aa
	printf("hasil kali :\n");
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            printf("%d\t", *C[i][j]);
        }
        printf("\n");
    }
printf("\n");

    pthread_t tid[20];

    int count =  0;
    int *data1 = NULL;
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            data1 = (int *)malloc(sizeof(int));

            data1 = C[i][j];

            pthread_create(&tid[count], NULL, addition, (void*)(data1));
	 /* Membuat thread pada array of thread tid pada indeks ke-indeks
            dengan memanggil fungsi addition dengan parameter data1 */
            count++;
        }
    }

	printf("hasil jumlah per elemen:\n");
    for(int i=0;i<20;i++){
        void *k;
        pthread_join(tid[i], &k); 
	/*join thread dengan return value k */

        int *p = (int *)k; //return value disimpan dalam variabel p
        printf("%d\t", *p);
        if ((i + 1) % 5 == 0){ // tiap 5 elemen, dicut buat dienter.. gitu pokoknya
            printf("\n");
        }
    }
    
    shmdt(C);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

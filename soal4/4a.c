#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
int (*hasil)[10];

void *matriks(void *arg)
{
    int matriks1[10][10];
    int matriks2[10][10];
    
    int i;
    int j;
    //printf("matriks 1 : \n"); 4x2
    
	matriks1[0][0]=1;
	matriks1[0][1]=2;

	matriks1[1][0]=2;
	matriks1[1][1]=4;

	matriks1[2][0]=1;
	matriks1[2][1]=2;

	matriks1[3][0]=3;
	matriks1[3][1]=1;
	   

    //printf("matriks 2: \n"); 2x5
    	matriks2[0][0]=1;
	matriks2[0][1]=2;
	matriks2[0][2]=0;
	matriks2[0][3]=4;
	matriks2[0][4]=1;

	matriks2[1][0]=3;
	matriks2[1][1]=1;
	matriks2[1][2]=2;
	matriks2[1][3]=0;
	matriks2[1][4]=1;
    
    int h;
    int jumlah=0;
    //hasil[i][j]=0;
    for(i = 0; i <= 3; i++){
        for(j = 0; j <= 4; j++){
	    //hasil[i][j]=0;
            for(h = 0; h <= 1; h++){
                jumlah = jumlah + (matriks1[i][h] * matriks2[h][j]);
            }
		hasil [i][j] = jumlah;
        }
    }
	return (*hasil);
}

int main()
{
	key_t key = 8808;
	int shmid = shmget (key, sizeof(int[10][10]), IPC_CREAT | 0666);
	hasil = shmat(shmid,0,0);
	
	if(shmid<0)
	{
		perror("shmget");
		exit(1)
	)
			
	int i;
	int j;

    printf("Hasil perkalian matriks: \n");
    for(i = 0; i < 4; i++){
        for(j = 0; j < 5; j++){
            printf("%d\t", hasil[i][j]);
        }
        printf("\n");
}
return 0;
}

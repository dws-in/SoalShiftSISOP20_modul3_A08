#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define M 4
#define K 2
#define N 5

void *multiply (void *param);

int A [M][K] = { {3,1}, {2,1}, {1,2}, {1,1} }; // Array ukuran M*K (4 baris 2 kolom)
int B [K][N] = { {1,5,2,1,4}, {10,5,12,1,1} }; // Array ukuran K*N (2 baris 5 kolom)
int (*C) [M][N]; // Array ukuran M*N (4 baris 5 kolom)

/* Structure untuk mem-passing data ke thread */
struct v
{
    int i; // Menunjukkan baris
    int j; // Menunjukkan kolom
};

int main()
{
    
    // shared memory tempelate
    key_t key=1234;
    int shmid = shmget(key, sizeof (int[20]), IPC_CREAT | 0666);
    C = shmat(shmid,0,0);
    
    pthread_t tid [M*N]; // Array of thread bernama tid dengan size M*N = 4*5
    int i; // Menunjukkan baris
    int j; // Menunjukkan kolom
    int indeks=0; // Menunjukkan indeks pada array of thread
    
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            struct v *data = (struct v*) malloc (sizeof (struct v));
            /* Membuat objek structure v bernama data
             dengan mengalokasikan memori sebesar size dari structure v */
            
            data -> i = i; // Mengeset nilai i pada objek structure v bernama data dengan nilai i
            data -> j = j; // Mengeset nilai j pada objek structure v bernama data dengan nilai j
            
            pthread_create (&tid[indeks++], NULL, multiply, (void *) data);
            /* Membuat thread pada array of thread tid pada indeks ke-indeks
             dengan memanggil fungsi multiply dengan parameter data */
        }
    }
    for (indeks=0; indeks < M*N; indeks++)
    {
        pthread_join(tid[indeks],NULL);
    }
    
    
    /* Mencetak hasil perkalian 2 Matriks */
    printf ("Hasil:\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf ("%d\t", *C[i][j]); // Output matriks C baris i kolom j
        }
        printf ("\n");
    }
    shmdt(*C);
    return 0;
}

/* Fungsi untuk melakukan perkalian 2 matriks */
void *multiply (void *param)
{
    struct v *par = (struct v*) param; // Mengeset objek structure v bernama par dengan param
    int h; // Variabel looping
    int i = par -> i; // Mengeset nilai i dengan nilai i pada par
    int j = par -> j; // Mengeset nilai j dengan nilai j pada par
    int hasil = 0; // Menunjukkan hasil perhitungan matriks
    
    for (h = 0; h < K; h++)
    {
        hasil += A[i][h] * B[h][j]; // Hasil didefiniskan dengan menambahkan semua hasil perkalian baris i kolom h dengan baris h kolom j
        *C[i][j] = hasil; // Mengeset nilai matriks C pada baris i dan kolom j dengan hasil
    }
    return(hasil);
}

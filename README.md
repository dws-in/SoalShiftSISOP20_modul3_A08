
# **SoalShiftSISOP20_modul3_A08**

##**Soal 3**
**soal3.c**

Program `soal3.c` digunakan untuk mengkategorikan file. program ini akan memindahkan file sesuai ekstensinya (tidak case sensitve, `.JPG` dan `.jpg` adalah sama) ke dalam directory sesuai ekstensinya yang hasilnya terdapat di working directory ketika program tersebut dijalankan. Directory ekstensi file dibuat secara otomatis. Apabila terdapat file yang tidak memiliki ekstensi maka akan dimasukkan ke dalam directory `Unknown`. 

Program `soal3.c` bisa di jalankan dalam 3 mode:
1. Mode `-f`, user bisa menambahkan argumen file yang akan dikategorikan sebanyak yang diinginkan.
2. Mode `-d`,  user bisa menginutkan 1 directory. Program akan mengkategorikan file di `path/to/directory` dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan.
3. Mode `*`, program akan mengkategorikan seluruh file yang ada di working directory ketika program tersebut dijalankan.

Dalam program ini terdapat 4 fungsi yaitu `getExt`, `isFile`, `*cat`, dan `main`. `getExt` digunakan untuk mendapatkan string ekstensi dari file. `isFile` digunakan untuk mengecek apakah path tersebut adalah file atau bukan. `*cat` digunakan untuk proses dalam thread. Setiap thread akan melakukan mengkategorikan 1 file saja. Dalam fungsi main mode akan diseleksi. Proses looping berjalan sesuai mode. Setelah itu thread dibuat untuk memproses 1 file tiap 1 kali pengulangan `err=pthread_create(&tid[n],NULL,&cat,(void *)argv[n+2]);`. Di dalam thread file dicek dengan fungsi `isFile` jika iya kemudian dicari ekstensinya dengan `getExt`, jika tidak maka akan keluar dari thread. Apabila directory dengan nama ekstensi tersebut belum ada maka dibuatlah directory. Lalu file dimasukkan kedalam directory tersebut `rename(oldP,newP);`. Setelah itu semua thread dijoin dan exit.


##**Soal 4**

**soal4a.c**
1. Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks.
Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di
dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
2. Tampilkan matriks hasil perkalian tadi ke layar.

```c
#define M 4
#define K 2
#define N 5

void *multiply (void *param);

int A [M][K] = { {3,1}, {2,1}, {1,2}, {1,1} }; // Array ukuran M*K (4 baris 2 kolom)
int B [K][N] = { {1,5,2,1,4}, {10,5,12,1,1} }; // Array ukuran K*N (2 baris 5 kolom)
int (*C) [M][N]; // Array ukuran M*N (4 baris 5 kolom)
```

Program diatas merupakan inisialisasi jumlah baris dan kolom matriks yang akan dibuat
dan beserta isi elemennya, serta inisialisasi fungsi perkalian matriks.

```c
struct v
{
    int i; // Menunjukkan baris
    int j; // Menunjukkan kolom
};
```

Program diatas merupakan Structure untuk mem-passing data ke thread.

```c
    // shared memory tempelate
    key_t key=1234;
    int shmid = shmget(key, sizeof (int[20]), IPC_CREAT | 0666);
    C = shmat(shmid,0,0);
    
    pthread_t tid [M*N]; // Array of thread bernama tid dengan size M*N = 4*5
    int i; // Menunjukkan baris
    int j; // Menunjukkan kolom
    int indeks=0; // Menunjukkan indeks pada array of thread
```

Di dalam fungsi main terdapat shared memory tempelate yang nantinya
akan digunakan untuk menampilkan hasil perkalian matriks ke layar
dan untuk mengerjakan soal 4b. 
Inisialisasi thread dengan variabel tid juga dilakukan, disini
saya akan menggunakan array of thread.

```c
 pthread_create (&tid[indeks++], NULL, multiply, (void *) data);
```

Membuat thread pada array of thread tid pada indeks ke-indeks 
dengan memanggil fungsi multiply dengan parameter data.

```c
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
```

Potongan program diatas digunakan untuk mencetak hasil dari perkalian matriks.

```c
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
```

Berikut merupakan fungsi untuk melakukan perkalian kedua matriks.



**soal4b.c**

```c
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
```
Program diatas berfungsi untuk mengambil data hasil perkalian matriks
dari program yang sebelumnya dengan menggunakan shared memory.

```c
pthread_t tid[20];
```
Inisialisasi variabel array of thread.

```c
    int count =  0;
    int *data1 = NULL;
    for(int i=0;i<4;i++){
        for(int j=0;j<5;j++){
            data1 = (int *)malloc(sizeof(int));

            data1 = C[i][j];

            pthread_create(&tid[count], NULL, addition, (void*)(data1));
```

Membuat thread pada array of thread tid pada indeks ke-indeks 
dengan memanggil fungsi addition dengan parameter data1.

```c
	printf("hasil jumlah per elemen:\n");
    for(int i=0;i<20;i++){
        void *k;
        pthread_join(tid[i], &k); 

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
```

digunakan join thread dengan return value k yang nantinya akan
disimpan ke dalam variabel p untuk mencetak hasil pertambahan
pada masing masing elemen.

```c
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
```

Fungsi untuk melakukan penjumlahan pada masing masing elemen matriks.


**soal4c.c**
1. Buatlah program C ketiga dengan nama "4c.c". 
Program ini tidak memiliki hubungan terhadap program yang lalu. 
2. Pada program ini, Norland diminta mengetahui jumlah file dan 
folder di direktori saat ini dengan command "ls | wc -l". Karena sudah 
belajar IPC, Norland mengerjakannya dengan semangat. (Catatan! : Harus menggunakan IPC Pipes) 

```c
	int fd1[2];
	int fd2[2];
	pid_t p; 
	
	if(pipe(fd1)==-1)
	{
		fprintf(stderr, "pipe error");
		return 1;
	}

	if((fork()) == 0)
	{
        dup2(fd1[1], 1); //output to fd1
        close(fd1[0]);
        close(fd1[1]);
        char *argv[4] = {"ls", NULL};
        execv("/bin/ls",argv);
	} 

    	if(pipe(fd2)==-1)
	return 1;

   	 else{
        dup2(fd1[0], 0);// input from fd1
        close(fd1[0]);
        close(fd1[1]);

        char *argv[4] = {"wc", "-l", NULL};
        execv("/usr/bin/wc",argv);
    }

```
di potongan kode ini bisa dilihat hanya menggunakan 1 fork sehingga
program yang dijalankan hanya ada 2 program.


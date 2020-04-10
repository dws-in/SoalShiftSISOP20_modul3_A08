
# **SoalShiftSISOP20_modul3_A08**

## Soal 3
   - **soal3.c**

Program `soal3.c` digunakan untuk mengkategorikan file. program ini akan memindahkan file sesuai ekstensinya (tidak case sensitve, `.JPG` dan `.jpg` adalah sama) ke dalam directory sesuai ekstensinya yang hasilnya terdapat di working directory ketika program tersebut dijalankan. Directory ekstensi file dibuat secara otomatis. Apabila terdapat file yang tidak memiliki ekstensi maka akan dimasukkan ke dalam directory `Unknown`. 

Program `soal3.c` bisa di jalankan dalam 3 mode:
1. Mode `-f`, user bisa menambahkan argumen file yang akan dikategorikan sebanyak yang diinginkan.
2. Mode `-d`,  user bisa menginutkan 1 directory. Program akan mengkategorikan file di `path/to/directory` dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan.
3. Mode `*`, program akan mengkategorikan seluruh file yang ada di working directory ketika program tersebut dijalankan.

Dalam program ini terdapat 4 fungsi yaitu `getExt`, `isFile`, `*cat`, dan `main`. `getExt` digunakan untuk mendapatkan string ekstensi dari file. `isFile` digunakan untuk mengecek apakah path tersebut adalah file atau bukan. `*cat` digunakan untuk proses dalam thread. Setiap thread akan melakukan mengkategorikan 1 file saja. Dalam fungsi main mode akan diseleksi. Proses looping berjalan sesuai mode. Setelah itu thread dibuat untuk memproses 1 file tiap 1 kali pengulangan `err=pthread_create(&tid[n],NULL,&cat,(void *)argv[n+2]);`. Di dalam thread file dicek dengan fungsi `isFile` jika iya kemudian dicari ekstensinya dengan `getExt`, jika tidak maka akan keluar dari thread. Apabila directory dengan nama ekstensi tersebut belum ada maka dibuatlah directory. Lalu file dimasukkan kedalam directory tersebut `rename(oldP,newP);`. Setelah itu semua thread dijoin dan exit.

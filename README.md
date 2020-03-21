# SoalShiftSISOP20_modul2_T16
- I Gede Arimbawa Teja Putra Wardana  || 05311840000045
- Desya Ananda Psupita Dewi           || 05311840000046

# Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:

   - Detik: 0-59 atau * (any value)
  
   - Menit: 0-59 atau * (any value)
  
   - Jam: 0-23 atau * (any value)
  
   - Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

Contoh: `./program \* 34 7 /home/somi/test.sh`

Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap detik pada jam 07:34.

### Soal 1.c

___Source code : [Soal 1.c](https://github.com/desyaapd/SoalShiftSISOP20_modul2_T16/blob/master/soal1FIX.c)___

Soal 1 merupakan program untuk membuat sebuah program deamon dengan ketentuan seperti diatas. Program yang telah kami buat sebagai berikut:

**Penyelesaian:**

```bash
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

int main(int argc, char** argv) {
pid_t pid, sid;    // Variabel untuk menyimpan PID
int sec,min,hour;

pid = fork();      // Menyimpan PID dari child process

if (pid < 0) {
exit(EXIT_FAILURE);
}

if (pid > 0) {
exit(EXIT_SUCCESS);
}

umask(0);
```
Dalam program Deamon, terkenal dengan proses yang bekerja secara background. Dalam prosesnya diperlukannya proses _forking_ yang kemudian membunuh parent yang ada. Kenapa dikatakan secara background, karena apabila parent telah dibunuh, maka akan ada child proses yang masih berjalan setelah dilakukannya _forking_ dari paren proses.

- `int main(int argc, char** argv` merupakan fungsi main dalam program. fungsi `argc` menunujukkan jumlah argumen yang digunakan, fungsi `argv ` merupakan penyimpanan argumen dalam bentuk array

- adanya fungsi `umask(0)` ini merupakan fungsi untuk mengubah mode file agar dapat dituis dan dibaca dengan benar.

```bash 
sid = setsid();
if (sid < 0) {
exit(EXIT_FAILURE);
}
if ((chdir("/home/desyaa")) < 0) {
exit(EXIT_FAILURE);
}
```
- pada fungsi `sid = setsid()`, proses akan mendapatkan sebuah **session ID** yang baru

- kemudian proses Deamon sendiri akan dipindahlan pembuatannya kedalam direktori baru dengan perintah `if ((chdir("/home/desyaa")) < 0) {exit(EXIT_FAILURE);}`

Untuk tujuan pengamanan dan mencegah terjadinya intervensi dari user, maka kita perlu melakukan penutupan terhadap tiga jenis descriptor standard I/O yaitu STDIN (standar input), STDOUT (standar output) dan STDERR (standar error) dalam pembuatan Deamon.


```bash
if(argc != 5){
	printf("failed to run");
return 0;
}
```
Program ini juga memiliki ketentuan untuk memasukkan argumen sebanyak 5(lima). seperti contoh yang ada diatas, `./program` terhitung sebagai argumen. apabila argumen yang dimasukkan kurang dari 5, maka program tidak berjalan dan menampilkan proses error dengan `printf("failed");`


```bash
sec = 0;
min = 0;
hour = 0;

   //argumen detik
   if(argv[1][0] == '*') {
       sec = 0;
   } else if(isalpha(argv[1][0])) {
       printf("input harus angka di argumen 1");
   } else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59) {
       printf("rangenya harus 0-59 detik atau *");
   } else {
       sec = atoi(argv[1]);
   }

   //argumen menit
   if(argv[2][0] == '*') {
       min = 0;
   } else if(isalpha(argv[2])) {
       printf("input harus angka di argumen 2");
   } else if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59) {
       printf("rangenya harus 0-59 menit atau *");
   } else {
       min = atoi(argv[2]);
   }

   //argumen jam
   if(argv[3][0] == '*') {
       hour = 0;
   } else if(isalpha(argv[3])) {
       printf("input harus angka di argumen 3");
   } else if(atoi(argv[3]) < 0 || atoi(argv[3]) > 23) {
       printf("rangenya harus 0-23 jam atau *");
   } else {
       hour = atoi(argv[3]);
   }

```
Program ini memiliki argumen `sec` detik, `min` menit, dan `hour`jam, sehingga argumen awal ketiga variable tersebut = 0

```
if(argv[1][0] == '*') {
       sec = 0;
   } else if(isalpha(argv[1][0])) {
       printf("input harus angka di argumen 1");
```       
- perintah diatas digunakan untuk melakukan pengecekan terhadap argumen masing masing dtik menit dan jam. argumen yang diinputkan disini dapat berupa value (bentuk angka) atau * untuk dideklarasi sebagai variable dari detik, menit atau jam.

- untuk batasan detik dan menit yaitu `atoi(argv[1]) > 59` dikarenakan 1 menit atau 1 detik batasnya sampai 60, lalu untuk jam memiliki batasan hingga `atoi(argv[3]) > 23` karena jam paling lama yaitu 24 jam

- penggunaan `atoi` berfungsi untuk mengonversi nilai string menjadi bilangan bertipe integer


```bash
  while(1){
    time_t t;
    struct tm tm = *localtime(&t);

    t = time(NULL);
```
- fungsi `while(1)` merupakan fungsi *looping* utama dari program Daemon karena program akan bekerja dalam jangka waktu tertentu.

- `time_t t;` merupakan penyimpanan waktu saat ini di dalam variabel `t`, kemudian `ptm = localtime(&t);` akan mengkonversikan nilai pada variable`t` menjadi waktu saat ini.


```bash

if((hour == tm.tm_hour || hour == 0) && (min == tm.tm_min || min == 0) && (sec == tm.tm_sec || sec == 0)) {
	if (fork()==0)
	  char *argx[] = {"bash",argv[4], NULL};
	  execv("/bin/bash", argx);
	  }
      }
    sleep(5);
  }
}
```
- `if((hour == tm.tm_hour || hour == 0) && (min == tm.tm_min || min == 0) && (sec == tm.tm_sec || sec == 0))` merupakan argumen untuk menyamakan jam yang ingin diinput oleh user dengan jam pada saat program itu dijalankan, jadi Daemon akan berjalan sesuai dengan argumen yang telah diinputkan.

- Jika kondisi tersebut telah terpenuhi, maka program akan menjalankan fungis _loop_ fork untuk melakukan bash pada script yang telah dibuat pada file `test.sh`

- Fungsi `while(1)` akan memberhentikan program sejenak dengan`sleep(5);` selama 5 detik sebelum melakukan proses looping lagi.




__Cara menjalankan program__

- Buatlah file sh untuk membuat file bash yang kelak akan berisi cron, saya memberi namanya dengan `test.sh`

- Kemudian file `test.sh` tersebut akan di bash untuk menghasilkan atau menunjukkan apakah file bash di dalamnya dapat berjalan, seperti pada gambar berikut

![bash](https://github.com/desyaapd/SoalShiftSISOP20_modul2_T16/blob/master/image/bash.png)

- Setelah semuanya berjalan, maka program deamon harus dicompile terlebih dahulu dengan `gcc 1.c –o 1`

- Setelah itu kita dapat memastikan apakah berjalan dengan perintah `./1 \* m h /home/desyaa/test.sh` , jadi menit dan jam disini dapat dirandom sesuai dengan input user

- Kemudian, cek apakah program berjalan dengan melihat isi dari `file.txt`

Hasil output dari program ini yaitu seperti berikut: 
![Capture](https://github.com/desyaapd/SoalShiftSISOP20_modul2_T16/blob/master/image/Capture.PNG)




### Kendala yang dialami

- Masih belum terlalu memahami soal dikarenakan terlalu banyak syarat atau ketentuan dalam mengerjakan soalnya

- Saat akan menjalankan programnya selalu terdapat banyak error ataupun warning yang kadang kami sendiri tidak bisa menyelesaikan dan membutuhkan waktu lama untuk menghilangkannya

- Serta dalam pengerjaan kurangnya komunikasi antar praktikan satu tim dikarenakan pengerjaannya yang bersifat online

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

___Source code : [Soal 1.c](https://github.com/desyaapd/SoalShiftSISOP20_modul2_T16/blob/master/1.c)___

Soal 1 merupakan program untuk membuat sebuah program deamon dengan ketentuan seperti diatas. Program yang telah kami buat sebagai berikut:

**Penyelesaian:**

```bash
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

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

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```
- pada fungsi `sid = setsid()`, proses akan mendapatkan sebuah **session ID** yang baru

- kemudian proses Deamon sendiri akan dipindahlan pembuatannya kedalam direktori baru dengan perintah `if ((chdir("/home/desyaa")) < 0) {exit(EXIT_FAILURE);}`

Untuk tujuan pengamanan dan mencegah terjadinya intervensi dari user, maka kita perlu melakukan penutupan terhadap tiga jenis descriptor standard I/O yaitu STDIN (standar input), STDOUT (standar output) dan STDERR (standar error) dalam pembuatan Deamon.


```bash
if(argc != 5){
	printf("failed");
return 0;
}
```
Program ini juga memiliki ketentuan untuk memasukkan argumen sebanyak 5(lima). seperti contoh yang ada diatas, `./program` terhitung sebagai argumen. apabila argumen yang dimasukkan kurang dari 5, maka program tidak berjalan dan menampilkan proses error dengan `printf("failed");`


```bash
sec = 0;
min = 0;
hour = 0;

if(sec = atoi(argv[1]) > 59 || atoi(argv[1]) < 0));
if(min = atoi(argv[2]) > 59|| atoi(argv[2]) < 0));
if(hour = atoi(argv[3]) > 24 || atoi(argv[3]) < 0));
```
Program ini memiliki argumen `sec` detik, `min` menit, dan `hour`jam, sehingga argumen awal ketiga variable tersebut = 0

- `if(sec = atoi(argv[1]) > 59 || atoi(argv[1]) < 0));`

- `if(min = atoi(argv[2]) > 59|| atoi(argv[2]) < 0));`

- `if(hour = atoi(argv[3]) > 24 || atoi(argv[3]) < 0));`

```bash
while(1){
time_t t;
struct tm* ptm;

t = time(NULL);
ptm = localtime(&t);
```
- fungsi `while(1)` merupakan fungsi *looping* utama dari program Daemon karena program akan bekerja dalam jangka waktu tertentu.

- `time_t t;` merupakan penyimpanan waktu saat ini di dalam variabel `t`, kemudian `ptm = localtime(&t);` akan mengkonversikan nilai pada variable`t` menjadi waktu saat ini.


```bash
if((hour == ptm->tm_hour || hour == 0) && (min == ptm->tm_min || min == 0) && (sec == ptm->tm_sec || sec == 0)) {
if (fork()==0)
char *argx[] = {"bash",argv[5], NULL};
execv("/bin/bash", argx);
	}
}
sleep(5);
}
```
- `if((hour == ptm->tm_hour || hour == 0)`

- `(min == ptm->tm_min || min == 0)`

- `(sec == ptm->tm_sec || sec == 0))`

-

Fungsi `while(1)` akan memberhentikan program sejenak dengan`sleep(5);` selama 5 detik sebelum melakukan proses looping lagi.


__Cara menjalankan program__

- Pertama, program harus dicompile terlebih dahulu dengan `gcc 1.c –o 1`

- Setelah itu kita dapat memastikan apakah berjalan dengan perintah `./1 \* m h /home/desyaa/test.sh` , jadi menit dan jam disini dapat dirandom sesuai dengan input user

- Kemudian, cek apakah program berjalan dengan cara `ps aux | grep test.sh`

Hasil output dari program ini yaitu seperti berikut: 
![SOAL1C](https://github.com/desyaapd/SoalShiftSISOP20_modul2_T16/blob/master/image/SOAL1C.PNG)


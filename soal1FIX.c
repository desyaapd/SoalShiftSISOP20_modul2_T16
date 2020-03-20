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
pid_t pid, sid;
int sec,min,hour;

pid = fork();

if (pid < 0) {
exit(EXIT_FAILURE);
}

if (pid > 0) {
exit(EXIT_SUCCESS);
}

umask(0);

sid = setsid();
if (sid < 0) {
exit(EXIT_FAILURE);
}
if ((chdir("/home/desyaapd")) < 0) {
exit(EXIT_FAILURE);
}

if(argc != 5){
	printf("failed to run");
return 0;
}

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

  while(1){
	time_t t;
	struct tm tm = *localtime(&t);

	t = time(NULL);

	if((hour == tm.tm_hour || hour == 0) && (min == tm.tm_min || min == 0) && (sec == tm.tm_sec || sec == 0)) {
		if (fork()==0)
		  char *argx[] = {"bash",argv[4], NULL};
		  execv("/bin/bash", argx);
	    }
      }
    sleep(5);
  }
}

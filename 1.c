#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

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
if ((chdir("/home/desyaa")) < 0) {
exit(EXIT_FAILURE);
}


close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);

if(argc != 5){
	printf("failed");
return 0;
}

sec = 0;
min = 0;
hour = 0;

if(sec = atoi(argv[1]) > 59|| atoi(argv[1]) < 0));
if(min = atoi(argv[2]) > 59 || atoi(argv[2]) < 0));
if(hour = atoi(argv[3]) > 24 || atoi(argv[3]) < 0));

while(1){
time_t t;
struct tm* ptm;

t = time(NULL);
ptm = localtime(&t);

if((hour == ptm->tm_hour || hour == 0) && (min == ptm->tm_min || min == 0) && (sec == ptm->tm_sec || sec == 0)) {
if (fork()==0)
char *argx[] = {"bash",argv[5], NULL};
execv("/bin/bash", argx);
	}
}
sleep(5);
}


#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;

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

  if ((chdir("/home/nandha/Documents/makanan")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    FILE* find;
    time_t t = time(NULL);
    const char *nama = "/home/nandha/Documents/makanan/makan_enak.txt";
    struct stat detail;
    stat(nama, &detail); 
    long int diff = t - detail.st_atime;
    if(diff<=30){
        int i = 1;
        while(1){
        char newname[500000]="makan_sehat.txt";
        sprintf(newname,"makan_sehat%d.txt",i);
        if(!(find=fopen(newname, "r"))){
            FILE* makenew = fopen(newname,"w");
            fclose(makenew);break;
        }
          i++;
        }
        


    }

    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}

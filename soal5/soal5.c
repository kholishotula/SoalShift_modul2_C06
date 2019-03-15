
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
  int i = 30;
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
      FILE *in, *out;
        char syslog[] = "/var/log/syslog"; char  isi[100000];
        char dirfile[1000];
        char dateTime[30];
        char loglog[100];
        char filename[1000];
        if(i==30){
        time_t timer = time(NULL);
        strftime(dateTime, 20, "%d:%m:%Y-%H:%M", localtime(&timer));
        sprintf(dirfile,"/home/nandha/log/%s", dateTime);
        mkdir(dirfile,ACCESSPERMS);
        i=1;
        }
      sprintf(loglog, "/log%d.log.txt",i);
      strcpy(filename,dirfile);
      strcat(filename,loglog);
      in = fopen(syslog, "r");
      out = fopen(filename,"w+");
     
    while((fgets(isi,sizeof(isi),in))!=NULL) {
        fputs(isi,out);
    }
    fclose(in);
    fclose(out);

      i++;
    sleep(60);
  }
  
  exit(EXIT_SUCCESS);
}
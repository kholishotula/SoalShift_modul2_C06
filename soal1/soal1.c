#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

while(1) {
 
	DIR *current;
	struct dirent *temp;
	current = opendir("/home/maya/sisop/modul2/Prak2/");
	char *lama;
  	char baru[200];
  	char dirlama[100];
  	strcpy(dirlama, "/home/maya/sisop/modul2/Prak2/");

	while( (temp = readdir(current)) != NULL)
     	{
        	int length = strlen(temp->d_name);
		lama = temp->d_name;
        	if(lama[length-4] == '.' && lama[length-3] == 'p' && lama[length-2] == 'n' && lama[length-1] == 'g')
        	{
            		strcpy(baru, "/home/maya/modul2/gambar/");
            		strcat(baru, lama);
		        length = strlen(baru);
            		baru[length-4] = '\0';
            		strcat(baru, "_grey.png");
          		strcat(dirlama, lama);
            		rename(dirlama, baru);
        	}
    	}
	
  	closedir(current);
  	sleep(5);
}
  
  exit(EXIT_SUCCESS);
}

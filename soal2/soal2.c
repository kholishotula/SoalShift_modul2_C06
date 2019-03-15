#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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
	      struct stat elen;
        char dir[100];
        strcpy(dir, "/home/maya/sisop/modul2/Prak2/hatiku/elen.ku");
        stat(dir, &elen);

        struct passwd *owner = getpwuid(elen.st_uid);
        struct group *group = getgrgid(elen.st_gid);

        char owner_name[100];
        strcpy(owner_name, owner->pw_name);

        char group_name[100];
        strcpy(group_name, group->gr_name);

        char data[100];
        strcpy(data, "www-data");

        if(strcmp(owner_name, data)==0 && strcmp(group_name, data)==0)
        {
                chmod(dir, 0777);
                remove(dir);
		            sleep(3);
        }
  }
  
  exit(EXIT_SUCCESS);
}

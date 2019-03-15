#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <string.h>

int main() {
    FILE *getPIDS;
    char line[130];
    getPIDS = popen("pidof /home/nandha/Documents/soal5/soal5","r");
    if(fgets(line,sizeof line,getPIDS)) {
            int pid = atoi(line);
            printf("KILL PID: %d\n",pid);
            kill(pid,SIGKILL);
    }

return 0;    
}
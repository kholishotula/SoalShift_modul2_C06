#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
    pid_t child1;
    pid_t child2;
    pid_t child3;
    int p11, p1[4];
    char isi[100000];

    child1 = fork();

    if(child1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);
    }else{
        int p2;
        while(wait(&p11)>0);
        pipe(p1);
        pipe(p1+2);
        child2 = fork();
        if(child2==0){
          close(p1[0]);
          close(p1[2]);
          close(p1[3]);
          dup2(p1[1], STDOUT_FILENO);
          close(p1[1]);
          execl("/bin/ls", "ls" ,"campur2", NULL);
        }else{
            child3 = fork();
            if(child3==0){
              close(p1[1]);
              dup2(p1[0],STDIN_FILENO);
              close(p1[0]);

              close(p1[2]);
              dup2(p1[3],STDOUT_FILENO);
              close(p1[3]);
              execl("/bin/grep", "grep" ,".txt$", NULL);
            }else{
              close(p1[1]);
              close(p1[0]);
              close(p1[3]);
              int x = read(p1[2],isi,sizeof(isi));
              close(p1[2]);
              FILE* output;
              output = fopen("daftar.txt","w+");
              fputs(isi,output);
              fclose(output);
            }
            
        }
    }
}
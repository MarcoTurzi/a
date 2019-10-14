#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
int fd;
void handler(int signo){
    char A,B,C;
    switch (signo){
        case SIGUSR1 :
        read(fd, &A, sizeof(int));
        lseek(fd,sizeof(int),SEEK_CUR);
        read(fd,&C,sizeof(int));
        if(A > C){
            lseek(fd,-sizeof(int),SEEK_CUR);
            write(fd,&A,sizeof(int));
        }
        break;
        case SIGUSR2 :
        lseek(fd,sizeof(int),SEEK_CUR);
        read(fd, &B, sizeof(int));
        read(fd, &C, sizeof(int));
        if(B > C){
            lseek(fd,-sizeof(int),SEEK_CUR);
            write(fd,&A,sizeof(int));
        }
        break;
        case SIGALRM :
            exit(1);
        break;
    }

}
int main(int argc, char*argv[]){

    int pid1,pid2;
    pid1 = fork();
    if(pid1 == 0){
        signal(SIGUSR1, &handler);
        signal(SIGUSR2, &handler);
        signal(SIGAlRM, &handler);
        fd = open(argv[1],O_RDWR,0777);
        while(1){
        
        pause();
        }
    }

    if(pid1 < 0){
        perror("Errore fork");
        exit(0);
    }




}
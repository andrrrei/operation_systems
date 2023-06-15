#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>


void child(int s) {
    printf("%s\n", "Ok");
}
 
void call(char * argv[], int ch[2], int n) {
    close(ch[n - 1]);
    dup2(ch[n % 2], n % 2);
    close(ch[n % 2]);
    execlp(argv[n], argv[n], NULL);
    exit(1);
}

int main(int argc, char * argv[]) {

    pid_t pid;
    signal(SIGCHLD, child);

    int ch[2];
    pipe(ch);
    
    if ((pid = fork()) == 0) { call(argv, ch, 1); }

    if ((pid = fork()) == 0) { call(argv, ch, 2); }

    wait(NULL);
    wait(NULL);
    close(ch[0]);
    close(ch[1]);
    
    return 0;
}
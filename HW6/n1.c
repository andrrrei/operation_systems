#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>

pid_t pr1, pr2;
bool flag = false;
int ok = 1;
int f;

void son(){
   printf("%s", "Son ");
   ok = print(f);
   putchar('\n');
   signal(SIGUSR1, son);
   kill(pr2, SIGUSR2);
}

void fath() {
    printf("%s", "Father ");
    signal(SIGUSR2, fath);
    ok = print(f);
    putchar('\n');
    kill(pr1, SIGUSR1);
}

void killer() { kill(getpid(), SIGKILL); }

void turn() { flag = true; }

int print(int f) {
    char c;
    while (read(f, &c, 1) == 1) {
        if (c == '\n' || c == ' ') { return 1; }
        putchar(c);
    }
    return 0;
}

int main(int argc, char * argv[]) {
    
    f = open(argv[1], O_RDONLY);
    if ((pr1 = fork()) != 0) { // если процесс отец
        signal(SIGUSR2, fath);
        signal(SIGCHLD, turn);
        while(flag == false & ok) { pause(); }
        wait(NULL);
        exit(0);
    }
    else {
        pr2 = getppid();
        signal(SIGALRM, killer);
        signal(SIGUSR1, son);
        kill(pr2, SIGUSR2);
        alarm(1);
        while(1 & ok) { pause(); }
    }

    return 0;
}
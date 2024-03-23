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

// Signal handler for the child process
void son() {
    printf("%s", "Son ");
    ok = print(f);
    putchar('\n');
    signal(SIGUSR1, son);
    kill(pr2, SIGUSR2);
}

// Signal handler for the parent process
void fath() {
    printf("%s", "Father ");
    signal(SIGUSR2, fath);
    ok = print(f);
    putchar('\n');
    kill(pr1, SIGUSR1);
}

// Signal handler to terminate the process
void killer() { 
    kill(getpid(), SIGKILL); 
}

// Signal handler to toggle flag
void turn() { 
    flag = true; 
}

// Function to read and print characters from a file descriptor
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
    
    // Parent process
    if ((pr1 = fork()) != 0) { 
        signal(SIGUSR2, fath);
        signal(SIGCHLD, turn);
        
        // Wait for flag to be set and child process to complete
        while(flag == false & ok) { 
            pause(); 
        }
        wait(NULL);
        exit(0); // Exit parent process
    }
    // Child process
    else {
        pr2 = getppid();
        signal(SIGALRM, killer);
        signal(SIGUSR1, son);
        
        // Notify the parent process and set alarm
        kill(pr2, SIGUSR2);
        alarm(1);
        
        // Wait indefinitely
        while(1 & ok) { 
            pause(); 
        }
    }

    return 0;
}

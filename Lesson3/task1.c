#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

// Signal handler for child processes
void child(int s) {
    printf("%s\n", "Ok");
}

// Function to execute child processes
void call(char *argv[], int ch[2], int n) {
    close(ch[n - 1]);
    dup2(ch[n % 2], n % 2);
    close(ch[n % 2]);
    execlp(argv[n], argv[n], NULL);
    exit(1); // Exit if execlp fails
}

int main(int argc, char *argv[]) {
    pid_t pid;
    signal(SIGCHLD, child); 

    int ch[2];
    pipe(ch); // Create a pipe

    // Create first child process
    if ((pid = fork()) == 0) { 
        call(argv, ch, 1); // Execute call function to replace child process with new program
    }

    // Create second child process
    if ((pid = fork()) == 0) { 
        call(argv, ch, 2); // Execute call function to replace child process with new program
    }

    wait(NULL); // Wait for the termination of any child process
    wait(NULL); // Wait for the termination of the second child process
    close(ch[0]); // Close the read end of the pipe
    close(ch[1]); // Close the write end of the pipe
    
    return 0;
}

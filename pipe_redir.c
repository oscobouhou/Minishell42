#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n = 3; // Number of commands
    int i;
    int pipefd[n-1][2]; // Pipes for n-1 commands
    pid_t pid;

    // Create the pipes
    i = 0;
    while (i < n-1) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Fork the child processes
    i = 0;
    while (i < n) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            // Child process
            if (i == 0) {
                // First command
                dup2(pipefd[i][1], STDOUT_FILENO);
            } else if (i == n-1) {
                // Last command
                dup2(pipefd[i-1][0], STDIN_FILENO);
            } else {
                // Intermediate commands
                dup2(pipefd[i-1][0], STDIN_FILENO);
                dup2(pipefd[i][1], STDOUT_FILENO);
            }

            // Close the unused file descriptors
            for (int j = 0; j < n-1; j++) {
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }

            // Execute the command
            execvp(argv[i+1], &argv[i+1]);

            // If execvp returns, it means there was an error
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    // Close the unused file descriptors
    for (int i = 0; i < n-1; i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }

    // Wait for the child processes to finish
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    return 0;
}
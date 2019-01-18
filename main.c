#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>

int main() {

    pid_t ret_val;
    int x = 0;

    ret_val = fork();
    if (ret_val != 0) {
        // for returned a non zero value (pid of child)
        // This code executes in the parent (parent runs this segment)
        pid_t pid_term = wait(&x);
        printf("Parent has ended\n");
    } else {
        // for returned 0 - this is a child process
        printf("In child...\n");
        printf("My process ID: %d\n", getpid());
        printf("My parent's ID: %d\n", getppid());
        printf("Calling execvp() to overwrite child process with one specified by execvp()\n");

        char *argv[4] = {"man", "-k", "pid", NULL};
        execvp(argv[0], argv);  // execvp requires the file name of the command followed by the entire argument list
    }

    int y = 0;
    int retVal = fork();
    if (retVal != 0) {
        wait(&y);
        printf("The child has completed.\n");
    } else {
        printf("In child process\n");
        char command[25];
        puts("Enter a batch command: ");
        fgets(command, 24, stdin);
        char *token = NULL;
        char *argv[25];
        token = strtok(command, " ");
        unsigned short i = 0;
        argv[i] = token;

        while (token != NULL) {
            i++;
            token = strtok(NULL, " ");
            argv[i] = token;
        }
        argv[i - 1][strlen(argv[i - 1]) - 1] = '\0';
        execvp(argv[0], argv);
    }

    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        puts("child process");
    } else {
        printf("Child process ID : %d \n", pid);
        sleep(30);
    }

    if (pid == 0)
        puts("end Child process");
    else
        puts("end parent process");
    return 0;
}
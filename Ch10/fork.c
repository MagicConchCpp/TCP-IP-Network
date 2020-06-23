#include <stdio.h>
#include <unistd.h>
// #include <sys/types.h>

int gval = 10;
int main(int argc, char *argv[]) {
    pid_t pid;
    int lval = 20;
    gval++, lval += 5;

    pid = fork();
    if (pid == 0)
        gval += 2, lval += 2;
    else
        gval -= 2, lval -= 2;
    
    if (pid == 0)
        printf("Child [%d, %d] \n", gval, lval);
    else
        printf("Parent [%d, %d] \n", gval, lval);
}
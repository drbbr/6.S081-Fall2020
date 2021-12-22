#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pid;
    int p1[2], p2[2];
    char buf1[10], buf2[10];
    pipe(p1);
    pipe(p2);
    pid = fork();
    if (pid == 0)
    {
        read(p2[0], buf2, 10);
        printf("%d: received %s\n", getpid(), buf2);
        write(p1[1], "pong", 5);
        exit(0);
    }
    else
    {
        write(p2[1], "ping", 5);
        read(p1[0], buf1, 10);
        printf("%d: received %s\n", getpid(), buf1);
    }
    exit(0);

    /*
    int pid;
    int p[2];
    char buf[10];
    pipe(p);
    pid = fork();
    if (pid == 0)
    {
        //printf("child:%d\n", getpid());
        read(p[0], buf, sizeof(buf));
        //close(p[0]);
        printf("%d: received %s\n", getpid(), buf);
        write(p[1], "pong", 5);
        //close(p[1]);
        exit(0);
    }
    else
    {
        //printf("parent:%d\n", getpid());
        write(p[1], "ping", 5);
        //close(p[1]);
        wait((int *)0);
        read(p[0], buf, sizeof(buf));
        //close(p[0]);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
    */
}
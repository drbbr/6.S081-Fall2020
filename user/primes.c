#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define NUM 35
void pipeprocess(int p[])
{
    int t;
    int n;
    int p_new[2];
    pipe(p_new);
    if (fork() == 0)
    {

        if (read(p[0], &t, sizeof(int)) != 0)
            printf("prime %d\n", t);
        else
            exit(0);
        while (read(p[0], &n, sizeof(int)) != 0)
        {
            if (n % t)
            {
                write(p_new[1], &n, sizeof(int));
            }
            if (n == NUM)
                break;
        }
        close(p[0]);
        close(p_new[1]);
        pipeprocess(p_new);
        wait(0);
        exit(0);
    }
    close(p[1]);
    wait(0);
}

int main(int argc, char *argv[])
{
    //primes version 2.0
    int i;
    int p[2];
    pipe(p);
    for (i = 2; i <= NUM; i++)
    {
        write(p[1], &i, sizeof(int));
    }
    pipeprocess(p);
    exit(0);
    /*
    ** primes version 1.0
    int i, x;
    int pid;
    int p[13][2];
    pipe(p[0]);
    pid = fork();
    x = 0;
    while (pid == 0)
    {
        int t, n;
        int a = 0;
        read(p[x][0], &t, sizeof(int));
        if (t == 0)
            exit(0);
        printf("prime %d\n", t);
        pipe(p[x + 1]); // open pipe for right
        for (; a <= 35; a++)
        {
            read(p[x][0], &n, sizeof(int));
            if (n == 0)
            {
                i = 0;
                write(p[x + 1][1], &i, sizeof(int));
                break;
            }
            if (n % t)
            {
                write(p[x + 1][1], &n, sizeof(int));
            }
        }
        close(p[x][0]);
        close(p[x + 1][1]);
        x++;
        if (pid != 0)
            exit(0);
    }
    if (pid != 0)
    {
        close(p[0][0]);
        for (i = 2; i <= 35; i++)
        {
            write(p[0][1], &i, sizeof(int));
        }
        i = 0;
        write(p[0][1], &i, sizeof(int));
        close(p[0][1]);
        for (i = 0; i < 11; i++)
        {
            wait(0);
        }
    }
    exit(0);
    */
}

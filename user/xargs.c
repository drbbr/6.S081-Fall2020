#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXARG 32

int main(int argc, char *argv[])
{
    int i;
    char ch;
    int argsidx = 0;
    int argsidx2 = 0;
    char *pattern = "";
    char *args[MAXARG];
    if (argc <= 1)
    {
        printf("need more arguments.\n");
        exit(1);
    }

    for (i = 1; i <= argc; ++i)
    {
        args[argsidx++] = argv[i];
    }
    argsidx = i - argc + 1;
    args[argsidx] = (char *)malloc(MAXARG);
    while (read(0, &ch, 1))
    {
        if (ch == '\n')
        {
            pattern[argsidx2++] = '\0';
            args[argsidx] = pattern;
            if (fork() == 0)
            {
                exec(args[0], args);
                exit(0);
            }
            wait(0);
            argsidx2 = 0;
            continue;
        }
        pattern[argsidx2++] = ch;
    }

    exit(0);
}
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find_file(char *path, char *find_name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    //printf("%s\n", path);
    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch (st.type)
    {
    case T_DIR:

        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while ((read(fd, &de, sizeof(de)) == sizeof(de)) && strcmp(de.name, "") != 0)
        {

            if (strcmp(de.name, ".") == 0) //. and ..
                continue;
            if (strcmp(de.name, "..") == 0) //. and ..
                continue;
            //printf("read %s\n", de.name);
            if (strcmp(find_name, de.name) == 0)
            {
                printf("%s/%s\n", path, de.name);
            }
            //printf("strcmp %s %s\n", find_name, de.name);
            // printf("buf now: %s\n", buf);
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = '\0';
            if (stat(buf, &st) < 0)
            {
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            if (st.type == 1)
            {
                //printf("buf now: %s\n", buf);
                find_file(buf, find_name);
            }
        }
        break;
    }
    close(fd);
}
int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("find need filename.\n");
        exit(1);
    }
    find_file(argv[1], argv[2]);
    exit(0);
}
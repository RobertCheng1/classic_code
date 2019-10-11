#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd, fd1, size;
    char buffer[80];
    fd = open("/root/tty_poc/file.c", O_RDONLY);
    printf("%d\n", fd);
    //fd1 = open("/root/tty_poc/file.c", O_RDONLY);
    //printf("%d\n", fd1);
    size = read(fd, buffer, sizeof(buffer));
    close(fd);
    printf("%s", buffer);
    return 0;
}


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

main(int argc, char*argv[])
{
const char * endstring = ".";
int fd;
printf("Before: %s's size = %d\n", argv[1], lseek(fd=open(argv[1], O_RDWR), 0, SEEK_END));
lseek(fd, atoi(argv[2]), SEEK_END);
write(fd, endstring, 1);
printf("After: %s's size = %d\n", argv[1], lseek(fd, 0, SEEK_END));
}

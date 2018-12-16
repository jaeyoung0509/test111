#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

main(int argc, char*argv[])
{
	printf("%s's size = %d\n", argv[1], lseek(open(argv[1], O_RDONLY), 0, SEEK_END));
}

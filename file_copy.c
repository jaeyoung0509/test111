#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

main(int argc, char*argv[])
{
	int src_fd, dst_fd;
	size_t rcnt;
	char buf[10];
	src_fd = open(argv[1], 0644);
	dst_fd = creat(argv[2], O_RDONLY);
	while((rcnt = read(dst_fd, buf, 10)) > 0)
		write(src_fd, buf, rcnt);
}

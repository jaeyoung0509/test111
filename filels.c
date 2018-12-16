#include <stdio.h>

#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
struct stat Info;
void main(int argc, char * argv[])
{
	stat(argv[1], &Info);
	printf("inode\t\tfilename\tfilesize\tlinks\tlocksize\tno of block\n");
	printf("%d\t%s\t%d\t\t%d\t%d\t\t%d\n", Info.st_ino, argv[1], Info.st_size, Info.st_nlink, Info.st_blksize, Info.st_blocks);
}

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

main(int argc, char * argv[])
{
	DIR * pdir = opendir(argv[1]);
	struct dirent * pde;
	int i = 0;
	while((pde = readdir(pdir)) != NULL) {
		printf("%20s ", pde->d_name);
		if(++i % 3 == 0)
			printf("\n");
	}
	closedir(pdir);
}

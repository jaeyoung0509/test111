#include <stdio.h>

main()
{
	char * const argv[] = {"ls", "-l", (char *) 0};
	execv("/bin/ls", argv);
}

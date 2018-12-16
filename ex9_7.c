#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
main()
{
	pid_t pid = fork();
	if(pid == 0)
	{
		execl("/bin/ls", "ls", "-l", (char *) 0);
		perror("execl failed");
	} else if(pid > 0)
	{
		wait((int *) 0);
		execlp("cal", "12", "2018",  (char *) 0);
		printf("is complete\n");
		exit(0);
	} else
		perror("fork failed");
}

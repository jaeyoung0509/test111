#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
main()
{
	int i = 0;
	pid_t pid;
	for( i = 0; i < 5; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			printf("child %d\n", getpid());
			exit(0);
		}
	}
}

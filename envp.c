#include <stdio.h>

int main(int argc, char * argv[], char*envp[])
{
	int i;
	for(i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	printf("%d\n", i);
}

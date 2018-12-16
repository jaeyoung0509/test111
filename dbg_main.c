#include <stdio.h>

extern int my_sum(int k);

main(int argc, char * argv[])
{
	int i;
	int k;
	int sum = 0;
	if(argc < 2)
	{
		fprintf(stderr, "Usage: dbg_main\n");
		exit(1);
	}
	k = atoi(argv[1]);
	sum = my_sum(k);
	printf("sim = %d\n", sum);
}

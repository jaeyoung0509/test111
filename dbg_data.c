#include <stdio.h>

int add(int i, int j)
{
	int k;
	k = i + j;
	return k;
}

main()
{
	int m = 2, n = 3;
	int sum;
	sum = m+n;
	printf("sum = %d\n", sum);
	sum = add(m,n);
	printf("sim = %d\n", sum);

}

# include <stdio.h>
# include <stdlib.h>

int main(int argc, char *argv[] )
{
	int n, cnt = 0;
	sscanf(argv[1],"%d", &n);
	for ( int i = 2; i <= n; i ++ )
	{
		int failed = 0;
		for( int j = 2; j * j <= i; j ++ )
		{
			if( i % j == 0 )
			{
				failed = 1;
			}
		}
		if( failed == 0 )
		{
			cnt ++;
		}
	}
	printf("There are %d prime numbers in [1 ... %d]\n", cnt, n);
}

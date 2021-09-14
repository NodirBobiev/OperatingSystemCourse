# include <stdio.h>
# include <stdlib.h>

int main( int argv, char *argc[])
{
	int n = 10;
	int pid = fork();
	for( int i = 0; i < n; i ++ )
	{
		if( pid > 0 )
		{
			printf("hello from parent [%d - %d]\n", pid, i);
		}
		else
		{
			printf("Hello from child [%d - %d]\n", pid, i);
		}
	}
	return 0;
}

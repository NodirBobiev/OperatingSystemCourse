# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

int main()
{
	for( int i = 0; i < 5; i ++ )
	{
		int pid = fork();
		printf("Process [%d %d]\n", pid, i);
		sleep(1);
	}
}


# include <stdio.h>
# include <stdlib.h>

int main()
{
	int pid = fork();
	printf("->%d\n", pid);
	int pid1 = fork();
	printf("-->%d %d\n", pid1, pid);
	int pid2 = fork();
	printf("--->%d %d %d\n", pid2, pid1, pid);
	int pid3 = fork();
	printf("---->%d %d %d %d\n", pid3, pid2, pid1, pid);
	return 0;
}

# include <stdio.h>
# include <stdlib.h>
# include <time.h>



int main()
{
	char filename[50], *argv[10];
	while( 1 ){
		printf("laptop@DEKSTOP-RAP6GU0:~$ ");
		scanf("%s", filename);
		// to read a line:
		int word = 0, id = 0;
		while( 1 )
		{
			int c = fgetc(stdin);
			if( c == EOF )
			{
				break;
			}
			if( c == ' ' )
			{
				word++;
				id = 0;
			}
			else
			{
				strncat(argv[word], &c, 1);
			}
		}
		int pid = fork();
		if( pid == 0 )
		{
			execve(filename, argv, NULL);
		}
	}
}

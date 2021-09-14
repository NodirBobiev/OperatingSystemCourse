# include <stdio.h>
# include <stdlib.h>
# include <time.h>



int main()
{
	char cmd[50];
	while( 1 ){

		printf("laptop@DEKSTOP-RAP6GU0:~$ ");
		scanf("%s", cmd);
		system(cmd);
	}
}

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main()
{
	int _10mb = 10 * 1024 * 1024;
	for( int i = 0; i < 10; i ++ ){
		int *array_ptr = malloc( _10mb );
		memset(array_ptr, 0, _10mb);
		printf("10 MB memory is alocated!\n");
		sleep(1);
	}

}

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main()
{
	void *a = malloc( 10*sizeof(int));
	for( int i = 0; i < 10; i ++ )
	{
		*((int *)a + i) = i;
	}
	void *b = malloc( 20*sizeof(int) );
	printf("\n");

	memcpy(b, a, 10 * sizeof(int) );
	free(a);
	a = b;
	for( int i = 0; i < 20; i ++ ){
		printf("%d ", *((int*)a + i));
	}
	printf("\n");
}

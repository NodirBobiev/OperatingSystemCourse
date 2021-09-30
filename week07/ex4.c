# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void my_realloc( void **ptr, size_t ptr_size, size_t new_size )
{
	if( new_size == 0 )
	{
		free(*ptr);
	}
	else if( !ptr )
	{
		*ptr = malloc( new_size );
	}
	else
	{
		void *temp = malloc( new_size );
		if( new_size <= ptr_size )
		{
			memcpy( temp, *ptr, new_size );
		}
		else
		{
			memcpy( temp, *ptr, ptr_size );
		}
		free( *ptr );
		*ptr = temp;
	}
}

int main()
{
	int n1;
	printf("Enter the size of Array: "); scanf("%d", &n1);
	int *array = malloc( n1 * sizeof(int) );
	for( int i = 0; i < n1; i ++ )
	{
		array[i] = 100;
	}
	for( int i = 0; i < n1; i ++ )
	{
		printf("%d ", array[i] );
	}
	printf("\n");


	int n2;
	printf("Enter the new size of Array: "); scanf("%d", &n2);
	my_realloc( &array, sizeof(int) * n1, sizeof(int) * n2 );
	for( int i = 0; i < n2; i ++ )
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

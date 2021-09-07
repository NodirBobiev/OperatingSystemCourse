# include <stdio.h>
# include <stdlib.h>
# include <time.h>
void swap( int *a, int *b )
{
	int c = *a;
	*a = *b;
	*b = c;
}

void buble_sort(int *array, int size)
{
	for( int i = 0; i < size; i ++ )
	{
		for( int j = 0; j < size-1; j ++ )
		{
			if( *(array+j) > *(array+j+1) )
			{
				swap( array+j, array+j+1);
			}
		}
	}
}
int main(int argc, char *argv[])
{
	srand(time(0));
	int size;
	if( argc > 1 )
	{
		sscanf(argv[1], "%d", &size);
	}
	else
	{
		printf("Enter the size of array: ");
		scanf("%d", &size);
	}
	int *arr = (int*) malloc(size*sizeof(int));
	for( int i = 0; i < size; i ++ )
	{
		*(arr+i) = rand() % (size+1);
	}
	
	printf("Initial array: ");
	for( int i = 0; i < size; i ++ )
	{
		printf("%d ", *(arr+i) );
	}
	buble_sort( arr, size);
	printf("\n\nArray after sorting: ");
	for( int i = 0 ; i < size; i ++ )
	{
		printf("%d ", *(arr+i));
	}
	printf("\n");
}

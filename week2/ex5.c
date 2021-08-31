# include <stdio.h>


void Type0( int n )
{
	for( int i = 0; i < n; i ++ )
	{
		for( int j = 0; j < n-i; j ++ )
		{
			printf(" ");
		}
		for( int j = 0; j < 2 * i + 1; j++ )
		{
			printf("*");
		}
		printf("\n");
	}
}
void Type1( int n )
{
	for( int i = 0; i < n; i++ )
	{
		for( int j = 0; j < i + 1; j ++ )
		{
			printf("*");
		}
		printf("\n");
	}
}
void Type2( int n )
{
	for( int i = 1; i < 2 * n; i++ )
	{
		for( int j = 0; j < (1-i/n) * i + (i/n)*(2*n-i); j++ )
		{
			printf("*");
		}
		printf("\n");
	}
}
void Type3( int n )
{
	for( int i = 0; i < n; i ++ )
	{
		for( int j = 0; j < n; j ++ )
		{
			printf("*");
		}
	printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int n, type;
	sscanf(*(argv+1),"%d", &n);
	sscanf(*(argv+2), "%d", &type);
	if( type == 0 )Type0(n);
	if( type == 1 )Type1(n);
	if( type == 2 )Type2(n); 
	if( type == 3 )Type3(n);
	
return 0;
}

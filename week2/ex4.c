# include <stdio.h>

void swap(int *a, int *b)
{
	int c = *a;
	*a = *b;
	*b = c;
}

int main()
{
	int a, b;
	printf("Enter first integer: ");
	scanf("%d", &a);
	printf("Enter second integer: ");
	scanf("%d", &b);
	swap( &a, &b );
	printf("%d %d\n", a, b);

	return 0;
}

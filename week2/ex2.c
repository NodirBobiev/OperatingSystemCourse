# include <stdio.h>
# include <string.h>
int main()
{
	char inputString[10000];
	printf("Enter a string: ");
	scanf("%s", inputString);
	int size = strlen(inputString);
	for( int i = size-1; i >= 0; i -- )
	{
		printf("%c", *(inputString + i));
	}
	printf("\n");

	return 0;
}

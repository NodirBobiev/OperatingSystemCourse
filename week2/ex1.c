# include <stdio.h>
# include <float.h>
# include <limits.h>
int main()
{
	int a = INT_MAX;
	float b = FLT_MAX;
	double c = DBL_MAX;
	printf("Integer size is %d and maximum value is %d\n", sizeof(a), a);
	printf("Float size is %d and maximum value is %f\n", sizeof(b), b);
	printf("Double size is %d and maximum value is %lf\n", sizeof(c), c);
	return 0;
}

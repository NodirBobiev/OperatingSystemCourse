# include <stdio.h>
# include <stdint.h>
# include <pthread.h>

void *myThread(void *i)
{
	// code
	printf(" >>Hello from myThread #%d\n", *(int *)i);
	pthread_exit(NULL);
}

int main()
{
	printf("Enter number N: ");
	int n;
	scanf("%d", &n);
	for( int i = 1; i <= n; i ++ ){
		pthread_t  thid;
		if( pthread_create(&thid, NULL, myThread, &i) )
		{
			printf(" >>ERROR IN CREATING Thread #%d!\n",i );
			pthread_exit(NULL);
			return 1;
		}
		else
		{
			printf(">>Thread #%d created!\n", i);
		}
		void *ret;
		if( pthread_join(thid, &ret) )
		{
			printf(" >>ERROR IN JOINING Thread #%d!\n", i);
			pthread_exit(NULL);
			return 1;
		}
		else
		{
			printf("  >>Thread #%d exited!\n", i);
		}
	}
	pthread_exit(NULL);
	return(0);

}

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/resource.h>

int main()
{
	int _10mb = 10 * 1024 * 1024;
	struct rusage usage;
	for( int i = 0; i < 10; i ++ ){
		int *array_ptr = malloc( _10mb );
		memset(array_ptr, 0, _10mb);
		printf("10 MB memory is alocated!\n");
		int res = getrusage(RUSAGE_SELF, &usage);
		printf("CPU time: %ld.%06ld sec user, %ld.%06ld sec system\n", 
			usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
			usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
		printf("Maximum size of resident set (kilobytes): %ld\n", usage.ru_maxrss);
		printf("Integral (shared) text memory size (kilobytes-seconds): %ld\n", usage.ru_ixrss);
		printf("Integral (unshared) data memory used (kilobytes-seconds): %ld\n", usage.ru_idrss);
		printf("Integral (unshared) stack memory used (kilobytes-seconds): %ld\n", usage.ru_isrss);
		printf("------------------------------------------------------------------------------\n");
		sleep(2);
	}

}

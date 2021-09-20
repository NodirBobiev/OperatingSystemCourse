# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <time.h>
# include <unistd.h>
# include <string.h>

# define BUFFERSIZE 4

int buffer[2*BUFFERSIZE] = {0};
int dataIndex = 0;
int isProducerSharingData = 1;

int newData()
{
	return rand() % 100;
}

void *producer(void *args)
{
	while( 1 )
	{
		if( isProducerSharingData )
		{
			if( dataIndex  < BUFFERSIZE )
			{
				int _newData = newData();
				buffer[dataIndex] = _newData;
				printf("Producer: New Data %d has been arrived and saved at %d.\n", _newData, dataIndex);
				dataIndex ++;
			}
			else
			{
				printf("*****Producer: Buffer is full!\n");
				isProducerSharingData = 0;
			}
		}
		usleep(500000);
	}
	pthread_exit(NULL);
	return 0;
}
void *consumer(void *args)
{
	while( 1 )
	{
		if( !isProducerSharingData )
		{
			if( dataIndex )
			{
				dataIndex--;
				int _takenData = buffer[dataIndex];
				printf("Consumer: Data %d at %d has been consumed.\n", _takenData, dataIndex);
			}
			else
			{
				printf("*****Consumer: There is no data to consume.\n");
				isProducerSharingData = 1;
			}
		}
		usleep(500000);
	}
	pthread_exit(NULL);
	return 0;
}
int main()
{
	srand( time(0) );
	pthread_t producer_t;
	pthread_t consumer_t;
	pthread_create(&producer_t, NULL, producer, NULL);
	pthread_create(&consumer_t, NULL, consumer, NULL);

	pthread_exit(NULL);
	return 0;
}

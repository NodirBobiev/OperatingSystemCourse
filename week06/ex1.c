# include <stdio.h>
# include <stdlib.h>
# include <time.h>

int main()
{
	srand(time(0));
	printf("--- First In First out algorithm ---\n");
	printf("Enter number of processes: ");
	int nProcess;
	scanf("%d", &nProcess);
	int *byArrivalTime = ( int* ) malloc( nProcess * sizeof( int ) );
	int *arrivalTime = ( int* ) malloc( nProcess * sizeof( int ) );
	int *burstTime = ( int* ) malloc( nProcess * sizeof( int ) );

	for( int i = 0; i < nProcess; i ++ )
	{
		byArrivalTime[i] = i;
		arrivalTime[i] = rand() % ( nProcess + 5 );
		burstTime[i] = rand() % ( 5 ) + 1;
	}
	printf("\nList of random generated processes:\n");
	printf("P#     AT    BT\n");
	for( int i = 0; i < nProcess; i ++ )
	{
		printf("P%-6d%-6d%-6d\n", i, arrivalTime[i], burstTime[i]);

        //printf("P%-6d", i); scanf("%d %d", arrivalTime+i, burstTime + i );
	}

	// Bubble sort to sort the processes based on the arrival time.
	for( int turn = 0; turn < nProcess-1; turn ++ )
	{
		for( int i = 0; i < nProcess-1; i ++ )
		{
			if( arrivalTime[ byArrivalTime[i] ] > arrivalTime[ byArrivalTime[i+1] ] )
			{
				int x = byArrivalTime[i];
				byArrivalTime[i] = byArrivalTime[i + 1];
				byArrivalTime[i + 1] = x;
			}
		}
	}

	printf("\nList of Processes after the sort(based on the arrival time).\n");
	printf("P#     AT    BT\n");
	for( int i = 0; i < nProcess; i ++ )
	{
		printf("P%-6d%-6d%-6d\n", 	byArrivalTime[i],
						arrivalTime[ byArrivalTime[i] ],
						burstTime[ byArrivalTime[i] ] );
	}


	printf("\nFinal Table:\n");
	printf("P#     AT    BT    CT    TAT   WT\n");
	int curTime = 0, sumTAT = 0, sumW = 0;
	for( int i = 0; i < nProcess; i ++ )
	{
		if( curTime < arrivalTime[ byArrivalTime[i] ] )
		{
			curTime = arrivalTime[ byArrivalTime[i] ];
		}
		int compT = curTime + burstTime[ byArrivalTime[i] ];
		int waitT = curTime - arrivalTime[ byArrivalTime[i] ];
		int tAroundT = waitT + burstTime[ byArrivalTime[i] ];
		printf("P%-6d%-6d%-6d%-6d%-6d%-6d\n", 	byArrivalTime[i],
							arrivalTime[ byArrivalTime[i] ],
							burstTime[ byArrivalTime[i] ],
							compT,
							tAroundT,
							waitT);
		sumTAT += tAroundT;
		sumW += waitT;
		curTime = compT;
	}
	double averageTAT = ( (double) sumTAT ) / nProcess;
	double averageW = ( (double) sumW ) / nProcess;
	printf("\nAverage Turnaround time = %f\n", averageTAT );
	printf("Average waiting time = %f\n", averageW );
}

/*
Don't forget that you are not alone. In the
most difficult moments, God is next to you.
			    - Omar Khayyam
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# define PERROR(s) {perror(s);exit(EXIT_FAILURE);}

struct Process{
	int id, at, bt, ct, wt, tat, order;
};

typedef int (* funcPtr_t)( struct Process* , struct Process*);

struct Process* CreateNewProcess( int id, int at, int bt )
{
	struct Process* prs = malloc(sizeof(struct Process));
	prs->id = id;
	prs->at = at;
	prs->bt = bt;
	prs->ct = 0;
	prs->wt = 0;
	prs->tat = 0;
	prs->order = 0;
	return prs;
}

void swap( struct Process* p1, struct Process* p2 )
{
	struct Process x = *p1;
	*p1 = *p2;
	*p2 = x;
}

int CompareFuncByArrivalTime(struct Process* p1, struct Process* p2)
{
	if( p1->at < p2->at )
	{
		return 1;
	}
	else if( p1->at > p2->at )
	{
		return 0;
	}
	else if( p1->bt < p2->bt )
	{
		return 1;
	}
	return 0;
}

int CompareFuncByBurstat(struct Process* p1, struct Process* p2)
{
	if( p1->bt < p2->bt )
	{
		return 1;
	}
	else if( p1->bt > p2->bt )
	{
		return 0;
	}
	else if( p1->at < p2->at )
	{
		return 1;
	}
	return 0;
}

int CompareFuncById(struct Process* p1, struct Process* p2)
{
	if( p1->id < p2->id )
	{
		return 1;
	}
	return 0;
}

struct Heap{
	struct Process* array;
	int capacity, size;
	funcPtr_t cFunc;
};

struct Heap* CreateNewHeap( int capacity, funcPtr_t cFunc )
{
	struct Heap* hp = malloc( sizeof(struct Heap) );
	hp->capacity = capacity;
	hp->size = 0;
	hp->array = malloc( capacity * sizeof(struct Process) );
	hp->cFunc = cFunc;
	return hp;
}

void AddToHeap( struct Heap* hp, struct Process* p )
{

	if( hp->size == hp->capacity )
	{
		PERROR("ERROR: Adding to full filled heap!");
	}
	int ind = hp->size ++;
	hp->array[ ind ] = *p;
	while( ind != 0 )
	{
		int par = ( ind - 1 ) / 2;
		if( hp->cFunc( hp->array + ind, hp->array + par ) )
		{
			swap( hp->array + ind, hp->array + par );
			ind = par;
		}
		else
		{
			break;
		}
	}
}
void RemoveFromHeap( struct Heap* hp )
{
	if( hp->size == 0 )
	{
		PERROR("ERROR: Removing from empty heap!");
	}
	int ind = 0;
	hp->array[ ind ] = hp->array[ --hp->size  ];
	while( ind < hp->size )
	{
		int leftchild = 2 * ind + 1, rightchild = 2 * ind + 2;
		int child = leftchild;
		if( leftchild >= hp->size )
		{
			break;
		}
		if( rightchild < hp->size && hp->cFunc( hp->array+ rightchild, hp->array + leftchild ) )
		{
			child = rightchild;
		}
		if( hp->cFunc( hp->array + child, hp->array + ind ) )
		{
			swap( hp->array + child, hp->array + ind );
			ind = child;
		}
		else
		{
			break;
		}
	}
}
struct Process GetHeapTop( struct Heap* hp )
{
	if( hp->size == 0 )
	{
		PERROR("ERROR: Accessing the top of empty heap!");
	}
	return hp->array[0];
}

void animate()
{
    char textAnimation[] = "\
\n\
    Author: Nodir Bobiev\n\
    Organization: Innopolis University\n\
    email: n.bobiev@innoopolis.university\n\
\n";
    int size = strlen(textAnimation);
    for( int i = 0; i < size; i ++ ){
        printf("%c", textAnimation[i]);
	fflush(stdout);
        usleep(1000000/60);
    }
}
int main()
{
    animate();
    srand(time(0));
	int nProcess;
	printf(">>> Enter the number of processes: "); scanf("%d", &nProcess);
	struct Heap* heapArrival = CreateNewHeap( 2*nProcess, CompareFuncByArrivalTime );
	struct Heap* heapBurst = CreateNewHeap( 2*nProcess, CompareFuncByBurstat );
	struct Heap* heapId = CreateNewHeap( 2*nProcess, CompareFuncById );

	printf("\nTable of randomly generated processes:\n");
	printf("P#    AT    BT\n");
	for( int i = 0; i < nProcess; i ++ )
	{
		int id = i + 1;
		int at = rand() % (i + 5);
		int bt = rand() % 8 + 1;
		printf("P%-5d%-6d%-6d\n", id, at, bt);
		AddToHeap( heapArrival, CreateNewProcess(id, at, bt) );
	}
	int curTime = 0, sumTAT = 0, sumWT = 0, nProcessed = 0;
	while( heapArrival->size + heapBurst->size )
	{
		if( heapBurst->size == 0 )
		{
            if( GetHeapTop( heapArrival ).at > curTime )
            {
                curTime = GetHeapTop( heapArrival ).at;
            }
        }
		while( heapArrival->size && GetHeapTop( heapArrival ).at <= curTime )
		{
			struct Process p = GetHeapTop( heapArrival );
			RemoveFromHeap( heapArrival );
			AddToHeap( heapBurst, &p );
		}

		struct Process p = GetHeapTop( heapBurst );
		RemoveFromHeap( heapBurst );
		p.wt = curTime - p.at;
		p.tat = p.wt + p.bt;
		p.ct = curTime + p.bt;
		p.order = ++nProcessed;
		AddToHeap( heapId, &p );
		curTime = p.ct;
		sumTAT += p.tat;
		sumWT += p.wt;
	}
	printf("\nTable of processes after processing:\n");
	printf("P#    AT    BT    CT    TAT   WT    order\n");
	while( heapId->size )
	{
		struct Process p = GetHeapTop( heapId );
		RemoveFromHeap( heapId );
		printf("P%-5d%-6d%-6d%-6d%-6d%-6d%-6d\n", p.id,p.at,p.bt, p.ct, p.tat, p.wt, p.order);
	}
	printf("Average Turnaround time = %f\n", (double)sumTAT / nProcess );
	printf("Average waiting time = %f\n", (double)sumWT / nProcess);
}

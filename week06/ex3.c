/*

	Don't forget that you are not alone. In the
	most difficult moments, God is next to you.
                                - Omar Khayyam

	In the name of the Lord of both wisdom and mind,
	To nothing sublimer can thought be applied,
	The Lord of whatever is named or assigned
	A place, the Sustainer of all and the Guide,
	The Lord of Saturn and the turning sky,
	Who causeth Venus, Sun, and Moon to Shine,
	Who is above conception, name, or Sign,
	The Artist of the heaven’s jewelry!
                                - Shahnama of Firdavsi
*/

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# define PERROR(s) {perror(s);exit(EXIT_FAILURE);}
///------------------------------------------------------------------------------------
int Max( int a, int b )
{
    return (a >= b ? a : b);
}
int Min( int a, int b )
{
    return (a <= b ? a : b);
}
void animate()
{
    char textAnimation[] = "\
\n\
    Author: Nodir Bobiev\n\
    Organization: Innopolis University\n\
    email: n.bobiev@innoopolis.university\n\
    Task: Round Robin Algorithm (Lab #6)\n\
\n";
    int size = strlen(textAnimation);
    for( int i = 0; i < size; i ++ ){
        printf("%c", textAnimation[i]);
	fflush(stdout);
        usleep(1000000/60);
    }
}



///------------------------------------------------------------------------------------
struct Process{
	int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turn_around_time;
};
typedef int (* funcPtr_t)( struct Process* , struct Process*);
struct Process* CreateNewProcess( int id, int at, int bt )
{
	struct Process* pcs = malloc( sizeof(struct Process) );
	pcs->id = id;
	pcs->arrival_time = at;
	pcs->burst_time = bt;
	pcs->remaining_time = bt;
	pcs->completion_time = 0;
	pcs->waiting_time = 0;
	pcs->turn_around_time = 0;
	return pcs;
}
int CompareFuncById(struct Process* p1, struct Process* p2)
{
    if( p1->id < p2->id )
    {
        return 1;
    }
    return 0;
}
int CompareFuncByArrivalTime(struct Process* p1, struct Process* p2)
{
	if( p1->arrival_time < p2->arrival_time )
	{
		return 1;
	}
	else if( p1->arrival_time > p2->arrival_time )
	{
		return 0;
	}
	else if( p1->id < p2->id )
	{
		return 1;
	}
	return 0;
}
void swap( struct Process** p1, struct Process** p2 )
{
	struct Process* x = *p1;
	*p1 = *p2;
	*p2 = x;
}
///---------------------------------------------------------------------------------------



struct Node
{
	struct Process* pcs;
	struct Node* next;
	struct Node* prev;
};
struct Node* CreateNode( struct Process* pcs )
{
	struct Node* nod = malloc( sizeof(struct Node) );
	nod->next = nod->prev = NULL;
	nod->pcs = pcs;
	return nod;
}
///----------------------------------------------------------------------------------------------



struct Queue
{
	struct Node* head;
	struct Node* tail;
	int size;
};
struct Queue* CreateQueue()
{
	struct Queue* queue = malloc( sizeof(struct Queue) );
	queue->head = queue->tail = NULL;
	queue->size = 0;
	return queue;
}
struct Process* GetFront( struct Queue* q )
{
	if( q->size == 0 )
	{
		PERROR("GetFront(): Queue is empty!");
	}
	return q->head->pcs;
}
void PushBack( struct Queue* q, struct Node* nod )
{
	if( nod == NULL )
	{
		PERROR("PushBack(): Adding null Node to Queue!");
	}
	if( q->size == 0 )
	{
		q->head = q->tail = nod;
	}
	else
	{
		q->tail->next = nod;
		q->tail = nod;
	}
	q->size ++;
}
void PopFront( struct Queue* q )
{
	if( q->size == 0 )
	{
		PERROR("PopFront(): Removing from empty Queue!");
	}
	struct Node* nod = q->head;
	q->head = q->head->next;
	q->size--;
	free(nod);
}
///-----------------------------------------------------------------------------------------



struct Heap{
    struct Process** array;
    int capacity, size;
    funcPtr_t cFunc;
};
struct Heap* CreateNewHeap( int capacity, funcPtr_t cFunc )
{
    struct Heap* hp = malloc( sizeof(struct Heap) );
    hp->capacity = capacity;
    hp->size = 0;
    hp->array = malloc( capacity * sizeof(struct Process*) );
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
    hp->array[ ind ] = p;
    while( ind != 0 )
    {
        int par = ( ind - 1 ) / 2;
        if( hp->cFunc( hp->array[ind], hp->array[par] ) )
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
        if( rightchild < hp->size && hp->cFunc( hp->array[rightchild], hp->array[leftchild] ) )
        {
            child = rightchild;
        }
        if( hp->cFunc( hp->array[child], hp->array[ind] ) )
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
struct Process* GetHeapTop( struct Heap* hp )
{
    if( hp->size == 0 )
    {
        PERROR("ERROR: Accessing the top of empty heap!");
    }
    return hp->array[0];
}
///-------------------------------------------------------------------------------




struct RoundRobin
{
	struct Queue* to_process_q;
    struct Heap* heap_arrival_time;
	struct Queue* completed_q;
	int quantum;
	int cur_time;
};
struct RoundRobin* CreateRoundRobin( int quantum )
{
	struct RoundRobin* alg = malloc( sizeof(struct RoundRobin) );
	alg->to_process_q = CreateQueue();
	alg->completed_q = CreateQueue();
    alg->heap_arrival_time = CreateNewHeap( 1000, CompareFuncByArrivalTime );
	alg->quantum = quantum;
	alg->cur_time = 0;
	return alg;
}
int IsThereAnyProcesses( struct RoundRobin* alg )
{
	return  !( alg->to_process_q->size + alg->heap_arrival_time->size == 0 );
}
void AddNewProcess( struct RoundRobin* alg, struct Process* pcs )
{
    AddToHeap( alg->heap_arrival_time, pcs );
}
void AssignNextTimeSlot( struct RoundRobin* alg )
{
	struct Process* q_pcs = NULL, *h_pcs = NULL;

	if( !alg->to_process_q->size && alg->heap_arrival_time->size )
    {
        q_pcs = GetHeapTop( alg->heap_arrival_time );
        RemoveFromHeap( alg->heap_arrival_time );
    }

	else if( alg->to_process_q->size )
    {
        q_pcs = GetFront( alg->to_process_q );
        PopFront( alg->to_process_q );
    }
    else
    {
        return;
    }

    int till_time_busy = Max( alg->cur_time, q_pcs->arrival_time ) + Min( alg->quantum, q_pcs->remaining_time );
    //printf("->-> %d %d\n",Max( alg->cur_time, q_pcs->arrival_time ), Min( alg->quantum, q_pcs->remaining_time ));
    while( alg->heap_arrival_time->size )
    {
        h_pcs = GetHeapTop( alg->heap_arrival_time );
        //printf(">>> %d %d %d\n", h_pcs->id, h_pcs->arrival_time, till_time_busy);
        if ( h_pcs->arrival_time <= till_time_busy )
        {
            PushBack(alg->to_process_q, CreateNode(h_pcs) );
            RemoveFromHeap( alg->heap_arrival_time );
        }
        else
        {
            break;
        }
    }

    alg->cur_time = Max( alg->cur_time, q_pcs->arrival_time );

    //printf("cur_time = %d  id = %d  at = %d  bt = %d  rt = %d  ct = %d  tat = %d\n", alg->cur_time, q_pcs->id, q_pcs->arrival_time, q_pcs->burst_time, q_pcs->remaining_time, q_pcs->completion_time, q_pcs->turn_around_time);
	if( q_pcs->remaining_time > alg->quantum )
	{
		q_pcs->remaining_time -= alg->quantum;
		alg->cur_time += alg->quantum;
		PushBack( alg->to_process_q, CreateNode( q_pcs ) );
	}
	else
	{
		alg->cur_time += q_pcs->remaining_time;
		q_pcs->completion_time = alg->cur_time;
		q_pcs->waiting_time = alg->cur_time - q_pcs->burst_time - q_pcs->arrival_time;
		q_pcs->turn_around_time = q_pcs->burst_time + q_pcs->waiting_time;
		q_pcs->remaining_time = 0;
		PushBack( alg->completed_q, CreateNode( q_pcs ) );
	}
}
///----------------------------------------------------------------------------------------




int main()
{
	animate();
    srand(time(0));
	int nProcess, quantum;
	printf(">>> Enter the number of processes: "); scanf("%d", &nProcess);
	printf(">>> Enter the quantum of the Round Robin algorithm: "); scanf("%d", &quantum);

	struct RoundRobin* alg = CreateRoundRobin( quantum );
    struct Heap* heapId = CreateNewHeap( 2*nProcess, CompareFuncById );

	printf("\nTable of randomly generated processes:\n");
	printf("P#    AT    BT\n");
	for( int i = 0; i < nProcess; i ++ )
	{
		int id = i + 1;

		int at = rand() % (i + 5);
		int bt = rand() % 8 + 1;
		printf("P%-5d%-6d%-6d\n", id, at, bt);

		//printf("P%-5d", id); scanf("%d %d", &at, &bt);

		AddNewProcess( alg, CreateNewProcess(id, at, bt) );
	}

    while( IsThereAnyProcesses( alg ) )
    {
        AssignNextTimeSlot( alg );
    }

    while( alg->completed_q->size )
    {
        AddToHeap( heapId, GetFront( alg->completed_q) );
        PopFront( alg->completed_q );
    }

	int sumTAT = 0, sumWT = 0;
	printf("\nTable of processes after processing:\n");
	printf("P#    AT    BT    CT    TAT   WT\n");
	while( heapId->size )
	{
		struct Process* p = GetHeapTop( heapId );
		RemoveFromHeap( heapId );
		printf("P%-5d%-6d%-6d%-6d%-6d%-6d\n", p->id, p->arrival_time, p->burst_time,
                                                    p->completion_time, p->turn_around_time, p->waiting_time);
        sumTAT += p->turn_around_time;
        sumWT += p->waiting_time;
	}
	printf("Average Turnaround time = %f\n", (double)sumTAT / nProcess );
	printf("Average waiting time = %f\n", (double)sumWT / nProcess);

}
/*
Test Case From slides:
0 1
0 2
0 4
0 6
0 8
11 8
11 6
11 4
11 2
11 1
*/

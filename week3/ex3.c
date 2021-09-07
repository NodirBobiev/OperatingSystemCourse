# include <stdio.h>
# include <stdlib.h>
# include <time.h>

struct LinkedList
{
	int val;
	struct LinkedList *next, *prev;
};

int n;
struct LinkedList *head = NULL;

void print_list( struct LinkedList *node )
{
	if( node != NULL )
	{
		printf("%d ", node->val);
		print_list(node->next);
	}
}

void insert_node( struct LinkedList *node, int newVal )
{
	struct LinkedList* newNode = (struct LinkedList*) malloc(sizeof(struct LinkedList));
	newNode->val = newVal;
	newNode->next = NULL;
	newNode->prev = node;
	node->next = newNode;
	n++;
}

void delete_node( struct LinkedList *node )
{
	if( node->next != NULL && node->prev != NULL )
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	else if( node->next != NULL )
	{
		node->next->prev = NULL;
		head = node->next;
	}
	else if( node->prev != NULL )
	{
		node->prev->next = NULL;
	}
	else{
		head = NULL;
	}
	free(node);
	n--;
}

int main()
{
	srand(time(0));
	printf("\nEnter the size of Linked List: ");
	int size;
	scanf("%d", &size);
	struct LinkedList *cur = NULL;
	for( int i = 0; i < size; i ++ )
	{
		int val = rand() % 1001;
		if( i )
		{
			insert_node(cur, val);
			cur = cur->next;
		}
		else
		{
			head = (struct LinkedList*) malloc(sizeof(struct LinkedList));
			head->prev = NULL;
			head->next = NULL;
			head->val = val;
			cur = head;
		}
	}
	printf("Initial array: "); 
	print_list(head);
	printf("\n\n");

	while( n )
	{
		int index = rand() % n;
		cur = head;
		for( int i = 0; i < index; i ++ )
		{
			cur = cur->next;
		}
		delete_node(cur);
		printf("%dth is deleted!\n", index);
		printf("Array after deleting: ");
		print_list(head);
		printf("\n\n");
	}
	return 0;
}

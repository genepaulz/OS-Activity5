#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"

Process newProcess(int id, int at, int bt, int wt, int tat){
	Process p = (Process)malloc(sizeof(struct process));
	p->id = id;
	p->at = at;
	p->bt = bt;
	p->wt = wt;
	p->tat = tat;
	p->index = 0;
	return p;
}

void displayProcess(Process p){
	printf("\nP%d:\n",p->id);
	printf("Burst time: %d\n",p->bt);
	printf("Arrival time: %d\n",p->at);
}

void destroyProcess(Process *p){
	printf("DELETED PROCESS P%d\n",(*p)->id);
	free(*p);
}

ProcessList newProcessList(int size){
	ProcessList pl = (ProcessList)malloc(sizeof(struct processList));
	pl->pl = (Process*)malloc( sizeof(struct process) * size);
	pl->count = 0;
	pl->size = size;
	return pl;
}

void expandProcessList(ProcessList pl, Process p){
	Process *x = (Process*)realloc(pl->pl,pl->size+1);
	pl->size++;
	pl->count++;
	pl->pl = x;
}

void addPProcess(ProcessList pl, Process p){
	if( pl->count == pl->size-1 ){
		expandProcessList(pl, p);
	}
	else{
	p->index = pl->count;
	pl->pl[pl->count] = p;
	pl->count++;
	}
}

void addCProcess(ProcessList pl, int id, int at, int bt, int wt, int tat){
	Process p = newProcess(id,at,bt,wt,tat);
	addPProcess(pl, p);
}

void displayProcessList(ProcessList pl){
	int i;
	printf("\nProcess List :\n");
	printf("Process	BT	AT	WT	TAT\n");
	for ( i = 0 ; i < pl->count ; i++){
		printf("P%d	%d	%d	%d	%d\n",pl->pl[i]->id, pl->pl[i]->bt, pl->pl[i]->at, pl->pl[i]->wt, pl->pl[i]->tat);
	}
}

void processFCFS(ProcessList pl){
	int CLOCK = 0;
	double AWT = 0.0f;
	double ATAT = 0.0f;
	Queue q = newQueue();
	
	int j, n = pl->count, processed = 0, current = 0;		
	
	while( processed < n ){
		
		for ( j = 0 ; j < n ; j ++ ){
			if( CLOCK == pl->pl[j]->at){
				enqueue(q,pl->pl[j]);
			}			
		}
		CLOCK++;
		if( !isEmpty(q) ){
			current++;
			if( current == head(q)->bt ){
				current = 0;
				
				pl->pl[head(q)->index] = head(q);
				pl->pl[head(q)->index]->tat = abs(CLOCK - pl->pl[head(q)->index]->at);
				ATAT += pl->pl[head(q)->index]->tat;
				pl->pl[head(q)->index]->wt = abs(pl->pl[head(q)->index]->tat - pl->pl[head(q)->index]->bt);
				AWT += pl->pl[head(q)->index]->wt;
				
				dequeue(q);
				processed++;
			}
		}	
	}	
	ATAT/=n;
	AWT/=n;
	
	displayProcessList(pl);
	printf("AveWT: %.2f\nAveTAT: %.2f",AWT,ATAT);
	printf("		FCFS Processing\n\n");
	destroy(&q);
}

void processSJF(ProcessList pl){
	int CLOCK = 0 ;
	double AWT = 0.0f;
	double ATAT = 0.0f;
	Queue q = newQueue();
	
	int i, n = pl->count, processed = 0, current = 0;
	
	while( processed < n ){
		
		if( current == 0 ){
			for ( i = 0 ; i < n ; i ++ ){
				if( CLOCK == pl->pl[i]->at){
					enqueue(q,pl->pl[i]);
				}			
			}
			sortQueue(q);
		}
		else{
			for ( i = 0 ; i < n ; i ++ ){
				if( CLOCK == pl->pl[i]->at){
					enqueue(q,pl->pl[i]);
				}			
			}
		}
		CLOCK++;
		if( !isEmpty(q) ){
			current++;
			if( current == head(q)->bt ){
				current = 0;
				
				pl->pl[head(q)->index] = head(q);
				pl->pl[head(q)->index]->tat = abs(CLOCK - pl->pl[head(q)->index]->at);
				ATAT += pl->pl[head(q)->index]->tat;
				pl->pl[head(q)->index]->wt = abs(pl->pl[head(q)->index]->tat - pl->pl[head(q)->index]->bt);
				AWT += pl->pl[head(q)->index]->wt;
				
				dequeue(q);
				processed++;
			}
		}
	}	
	ATAT/=n;
	AWT/=n;
	
	displayProcessList(pl);
	printf("AveWT: %.2f\nAveTAT: %.2f",AWT,ATAT);
	printf("		SJF Processing\n\n");
	destroy(&q);
}

void destroyProcessList(ProcessList *pl){
	(*pl)->pl = NULL;
	free((*pl)->pl);
	free(*pl);
}

Queue newQueue(){
	Queue q = (Queue)malloc(sizeof(struct queue));
	q->front = q->rear = NULL;
	q->count = 0;
	return q;
}
nodeptr createNode(qItem item){
	nodeptr p = (nodeptr)malloc(sizeof(struct node));
	p->p = item;
	p->next = p->prev = NULL;
	return p;
}
void enqueue(Queue q, qItem item){
	nodeptr temp = createNode(item);
	if( q->rear != NULL ){
		temp->prev = q->rear;
		q->rear->next = temp;
		q->rear = temp;
	}		
	else{
		q->front = temp;
	}
	q->rear = temp;
	q->count++;
}

void dequeue(Queue q){
	nodeptr p = q->front;
	if( p != NULL ){
		q->front = p->next;
		p->prev = p->next = NULL;
		free(p);
		if( q->front == NULL)
			q->rear = NULL;
			
		q->count--;
	}
}

void sortQueue(Queue q){
	int i, key, j;
	Process swap1,swap2;
	int n = q->count;
	Process p[q->count];
	for( i = 0 ; i < n ; i++ ){
		p[i] = head(q);
		dequeue(q);
	}
	
    for (i = 1; i < n; i++) {
        key = p[i]->bt;
        swap1 = p[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && p[j]->bt > key) {
        	swap2 = p[j];
            p[j + 1] = swap2;
            j = j - 1;
        }
        p[j + 1] = swap1;
    }
	for( i = 0 ; i < n ; i++ ){
		enqueue(q,p[i]);
	}
}

void removeItem(Queue q, qItem item){
	nodeptr p = q->front;
	if( p != NULL ){
		while( p != NULL ){
			if( p->p == item ){
				if( p == q->front ){
					dequeue(q);
				}
				else if( p == q->rear ){
					q->rear = p->prev;
					p->prev = p->next = NULL;
					free(p);
				}
			}
			p = p->next;
		}
		q->count--;
	}
}

int isEmpty(Queue q){
	return q->count == 0;
}

void clear(Queue q){
	while( !isEmpty(q) ){
		dequeue(q);
	}
}

qItem head(Queue q){
	return q->front->p;
}
qItem tail(Queue q){
	return q->rear->p;
}

int contains(Queue q, qItem x){
	int flag = 0;
	nodeptr p = q->front;
	while( p != NULL ){
		if(p->p == x){
			flag = 1;
			break;
		}
		
		p = p->next;
	}
	return flag;
}

void display(Queue q){
	printf("Queue Contains :\n");
	printf("ID	AT	BT	WT	TAT\n");
	nodeptr p = q->front;
	while( p != NULL ){
		printf("P%d	%d	%d	%d	%d\n",p->p->id, p->p->at, p->p->bt, p->p->wt, p->p->tat);		
		p = p->next;
	}
}
void destroy(Queue *q){
	clear(*q);
	free(*q);
	*q = NULL;
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
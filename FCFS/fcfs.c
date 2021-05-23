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
	printf("ID	AT	BT	WT	TAT\n");
	for ( i = 0 ; i < pl->count ; i++){
		printf("P%d	%d	%d	%d	%d\n",pl->pl[i]->id, pl->pl[i]->at, pl->pl[i]->bt, pl->pl[i]->wt, pl->pl[i]->tat);
	}
}

//void processFCFS(ProcessList pl){
//	int CLOCK = 0;
//	double AWT = 0.0;
//	double ATAT = 0.0;
//	int tbt = 0;
//	int i, id, at, bt, wt, tat, j;
//	
//    for (i = 1; i < pl->count; i++) {
//    	id = pl->pl[i]->id;
//        at = pl->pl[i]->at;
//        bt = pl->pl[i]->bt;
//        wt = pl->pl[i]->wt;
//        tat = pl->pl[i]->tat;
//        j = i - 1; 
//        
//        while (j >= 0 && pl->pl[j]->at > at) {
//            pl->pl[j + 1]->at = pl->pl[j]->at;
//            pl->pl[j + 1]->id = pl->pl[j]->id;
//            pl->pl[j + 1]->bt = pl->pl[j]->bt;
//            pl->pl[j + 1]->wt = pl->pl[j]->wt;
//            pl->pl[j + 1]->tat = pl->pl[j]->tat;
//            j = j - 1;
//        }
//        pl->pl[j + 1]->id = id;
//        pl->pl[j + 1]->at = at;
//        pl->pl[j + 1]->bt = bt;
//        pl->pl[j + 1]->wt = wt;
//        pl->pl[j + 1]->tat = tat;
//    }    
//   	for(i = 0 ; i < pl->count ; i++ ){
//   		CLOCK+= pl->pl[i]->bt;
//   		tbt+=pl->pl[i]->bt;
//   		pl->pl[i]->tat = abs(CLOCK - pl->pl[i]->at);
//   		ATAT += pl->pl[i]->tat;
//   		pl->pl[i]->wt = abs(pl->pl[i]->tat - pl->pl[i]->bt);
//   		AWT += pl->pl[i]->wt;
//	}
//	ATAT/=pl->count+1;
//	AWT/=pl->count+1;
//	printf("\nFCFS\n");
//	printf("Process	AT	BT	WT	TAT\n");
//	for( i = 0 ; i < pl->count ; i++ ){
//		printf("P%d	%d	%d	%d	%d\n",pl->pl[i]->id, pl->pl[i]->at, pl->pl[i]->bt, pl->pl[i]->wt, pl->pl[i]->tat);
//	}
//	printf("AveWT: %.2f\nAveTAT: %.2f",AWT,ATAT);
//	printf("\n%d\n",tbt);
//}

void processFCFS(ProcessList pl){
	int CLOCK = 0;
	double AWT = 0.0f;
	double ATAT = 0.0f;
	Queue q = newQueue();
	
	int i;
	int n = pl->count;
	int tbt;
	for( i = 0; i < n; i++ ){
		tbt += pl->pl[i]->bt;
	}
	int j;
	
	int processed = 0;
	int current = 0;
	int sum = 0;
	
	ProcessList done = newProcessList(n);
	
	while( processed < n ){
		
		for ( j = 0 ; j < n ; j ++ ){
			if( CLOCK == pl->pl[j]->at){
				enqueue(q,pl->pl[j]);
			}			
		}
		CLOCK++;
		if( !isEmpty(q) ){
			current--;
			sum = current + head(q)->bt;
			if( sum == 0 ){
				current = 0;
				sum = 0;
				
				done->pl[processed] = head(q);
				done->count++;
				done->pl[processed]->tat = abs(CLOCK - done->pl[processed]->at);
				ATAT += done->pl[processed]->tat;
				done->pl[processed]->wt = abs(done->pl[processed]->tat - done->pl[processed]->bt);
				AWT += done->pl[processed]->at;
				
				dequeue(q);
				processed++;
			}
		}	
	}	
	ATAT/=n;
	AWT/=n;
	displayProcessList(done);
	printf("AveWT: %.2f\nAveTAT: %.2f",AWT,ATAT);
	printf("		FCFS Processing\n\n");
	destroyProcessList(&done);
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
}

void dequeue(Queue q){
	nodeptr p = q->front;
	if( p != NULL ){
		p->prev = NULL;
		q->front = p->next;
		free(p);
		if( q->front == NULL)
			q->rear = NULL;
	}
}

int isEmpty(Queue q){
	return q->front == NULL;
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

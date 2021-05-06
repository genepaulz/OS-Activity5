#include <stdio.h>
#include <stdlib.h>
#include "sjf.h"

Queue newQueue(int size){
	Queue q  = (Queue)malloc(sizeof(struct queue));
	q->items = (qItem *)malloc(sizeof(qItem)*size);
	q->size = size;
	q->head = 0;
	q->tail = 0;
	q->count = 0;
	return q;
}

void destroy(Queue *q){
	free((*q)->items);
	free(*q);
	*q=NULL;
}

void display(const Queue q){
	printf("\nELEMENTS IN QUEUE : ");
	int i=q->head;
	int j;
	for( j=0 ; j < q->count ; j++){
		printf("%d ",q->items[i]);
		i = next(q,i);
	}
}

int next(Queue q,int pos){
	return (pos+1)%q->size;
}

void insertionSort(int arr[], int n){
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

void enqueue(Queue q, qItem item){
	if( q->count < q->size ){
		q->items[q->tail] = item;
		q->tail = next(q,q->tail);
		q->count++;
		insertionSort(q->items,q->count);
	}
	else{
		printf("\nQueue is FULL CANNOT ENQUEUE");
	}
}
void enqueueN(Queue q, qItem item){
	if( q->count < q->size ){
		q->items[q->tail] = item;
		q->tail = next(q,q->tail);
		q->count++;
	}
	else{
		printf("\nQueue is FULL CANNOT ENQUEUE");
	}
}

void dequeue(Queue q){
	if( q->count != 0 ){
		q->head = next(q,q->head);
		q->count--;
	}
}

int isEmpty(Queue q){
	return q->count == 0;
}

int isFull(Queue q){
	return q->count == q->size;
}

void clear(Queue q){
	q->count = q->head = q->tail = 0;
}

int head(Queue q){
	return q->items[q->head];
}

int tail(Queue q){
	return q->items[q->count-1];
}


int CLOCK = -1;
float AWT = 0.0;
float ATAT = 0.0;
void resetClock(){
	CLOCK = -1;
}
void resetAWT(){
	AWT = 0.0;
}
void resetATAT(){
	ATAT = 0.0;
}

Process newProcess(int id,int bt, int at, int wt, int tat){
	return (Process) {id,bt,at,wt,tat};
}
void displayProcess(Process p){
	printf("\nP%d:\n",p.id);
	printf("Burst time: %d\n",p.bt);
	printf("Arrival time: %d\n",p.at);
}
void processSJF(Process p[],int TESTSIZE){
	int i;
	Queue q = newQueue(10);
	for( i = 0; i < TESTSIZE; i++ ){
		enqueue(q,p[i].bt);
	}
	int deqC=0;
	while( deqC<TESTSIZE ){
		for( i = 0; i < TESTSIZE; i++ ){
			if(head(q) == p[i].bt){
				enqueueN(q,p[i].id);
				dequeue(q);
			}
		}
		deqC++;
	}
	CLOCK = 0;
	while( !isEmpty(q) ){
		CLOCK += p[head(q)-1].bt;
		p[head(q)-1].tat = CLOCK - p[head(q)-1].at;
		ATAT += p[head(q)-1].tat;
		p[head(q)-1].wt = p[head(q)-1].tat - p[head(q)-1].bt;
		AWT += p[head(q)-1].wt;
		dequeue(q);
	}
	ATAT/=TESTSIZE;
	AWT/=TESTSIZE;
	
	printf("Process	BT	AT	WT	TAT\n");
	for( i = 0 ; i < TESTSIZE ; i++ ){
		printf("P%d	%d	%d	%d	%d\n",p[i].id,p[i].bt,p[i].at,p[i].wt,p[i].tat);
	}
	printf("\nAveWT: %.2f\nAveTAT: %.2f\n",AWT,ATAT);
	resetAWT();
	resetATAT();
	resetClock();
	clear(q);
	destroy(&q);
}

void processSJFwithAT(Process p[],int TESTSIZE){
	int i;
	Queue q = newQueue(10);
	CLOCK = 0;
	int enqC = 0;
	int go = 1;
	while( go ){
		while( enqC < TESTSIZE ){
			for( i = 0 ; i < TESTSIZE ; i++ ){
				if( CLOCK == p[i].at ){
					enqueue(q,p[i].bt);
					enqC++;
				}
			}			
			CLOCK++;
		}
		while( enqC > 0 ){
			for( i = 0 ; i < TESTSIZE ; i++ ){
				if( head(q) == p[i].bt ){
					enqueueN(q,p[i].id);
					dequeue(q);			
					enqC--;
				}
			}
		}
		CLOCK = p[head(q)-1].at;
		while( !isEmpty(q) ){
			CLOCK += p[head(q)-1].bt;
			p[head(q)-1].tat = CLOCK - p[head(q)-1].at;
			ATAT += p[head(q)-1].tat;
			p[head(q)-1].wt = p[head(q)-1].tat - p[head(q)-1].bt;
			AWT += p[head(q)-1].wt;
			dequeue(q);
		}
		if( isEmpty(q) )
		go = 0;
	}
	
	ATAT/=TESTSIZE;
	AWT/=TESTSIZE;
	printf("Process	BT	AT	WT	TAT\n");
	for( i = 0 ; i < TESTSIZE ; i++ ){
		printf("P%d	%d	%d	%d	%d\n",p[i].id,p[i].bt,p[i].at,p[i].wt,p[i].tat);
	}
	printf("\nAveWT: %.2f\nAveTAT: %.2f\n",AWT,ATAT);
	resetAWT();
	resetATAT();
	resetClock();
	clear(q);
	destroy(&q);
}

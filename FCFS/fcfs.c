#include <stdio.h>
#include <stdlib.h>
#include "fcfs.h"

//QUEUE CODE

Queue newQueue(){
    Queue q = (Queue)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue q,qItem item){
    nodeptr temp = (nodeptr)malloc(sizeof(struct queue));
    temp->item = item;
    temp->next = NULL;

    if( q->rear != NULL )
        q->rear->next = temp;    
    else
        q->front = temp;    
    q->rear = temp;
}

void dequeue(Queue q){
    nodeptr p = q->front;
    if( p != NULL){
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
	if( !isEmpty(q) )
    	return q->front->item;
    else {
    	printf("\nQueue is EMPTY cannot ACQUIRE HEAD");
    	return -1;
	}
}

qItem tail(Queue q){
	if( !isEmpty(q) )
    	return q->rear->item;
    else {
    	printf("\nQueue is EMPTY cannot ACQUIRE TAIL");
    	return -1;
	}
}

int contains(Queue q, qItem x){
	int flag = 0;
	if( !isEmpty(q) ){
		nodeptr p = q->front;
		while ( p!=NULL ){
			if( p->item == x){
				flag = 1;
				break;
			}			
		}
	}
	return flag;
}

void display(Queue q){
    if(!isEmpty(q)){
        printf("\nElements in Queue : ");
        nodeptr p = q->front;
        while( p != NULL ){
            printf("%d ",p->item);
            p = p->next;
        }
    }
    else printf("\nElements in Queue : ");
}

void destroy(Queue *q){
	clear(*q);
	free(*q);
	*q=NULL;
}

// PROCESS CODE

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
void processFCFS(Process p[],int TESTSIZE){
	int i;
	Queue q = newQueue();
	for( i = 0; i < TESTSIZE; i++ ){
		enqueue(q,p[i].id);
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
	printf("\nAveWT: %.2f\nAveTAT: %.2f",AWT,ATAT);
	resetAWT();
	resetATAT();
	resetClock();
	destroy(&q);
}


#ifndef FCFS_H
#define FCFS

typedef int qItem;

typedef struct node *nodeptr;
struct node{
	qItem item;
	nodeptr next;
};

struct queue{
	nodeptr front;
	nodeptr rear;
};

typedef struct queue *Queue;

Queue newQueue();
void enqueue(Queue q,qItem item);
void dequeue(Queue q);
int isEmpty(Queue q);
void clear(Queue q);
qItem head(Queue q);
qItem tail(Queue q);
int contains(Queue q, qItem x);
void display(Queue q);
void destroy(Queue *q);

struct process{
	int id;
	int bt;
	int at;
	int wt;
	int tat;
};

typedef struct process Process;

Process newProcess(int id,int bt, int at, int wt, int tat);
void displayProcess(Process p);
void processFCFS(Process p[],int TESTSIZE);
#endif

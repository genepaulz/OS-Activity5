#ifndef SJF_H
#define SJF

typedef int qItem;
struct queue{
	qItem *items;	
	int size;
	int head;
	int tail;
	int count;
};

typedef struct queue *Queue;

Queue newQueue(int size);
void destroy(Queue *q);
void display(const Queue q);
void enqueue(Queue q, qItem item);
void dequeue(Queue q);
int isEmpty(Queue q);
int isFull(Queue q);
void clear(Queue q);
int head(Queue q);
int tail(Queue q);

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
void processSJF(Process p[],int TESTSIZE);


#endif

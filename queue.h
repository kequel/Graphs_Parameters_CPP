#ifndef QUEUE_H
#define QUEUE_H

typedef struct list {
    int value;
    struct list* next;
} queueType;

typedef struct {
    queueType* front;
    queueType* rear;
} Queue;

void initQueue(Queue* queue);
void addToQueue(Queue* queue, int value);
int isQueueEmpty(Queue* queue);
int popQueue(Queue* queue);
int front(Queue* queue);
void clearQueue(Queue* queue);

#endif

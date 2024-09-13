#include "queue.h"
#include <cstdlib>

void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void addToQueue(Queue* queue, int value) {
    queueType* newNode = (queueType*)malloc(sizeof(queueType));
    newNode->value = value;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

int popQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;
    }
    int element = queue->front->value;
    queueType* toBeRemoved = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(toBeRemoved);
    return element;
}

int front(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return -1;
    }
    return queue->front->value;
}

void clearQueue(Queue* queue) {
    while (!isQueueEmpty(queue)) {
        popQueue(queue);
    }
}

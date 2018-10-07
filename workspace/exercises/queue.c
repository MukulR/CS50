#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>

typedef struct IntQueue{
    int capacity;
    int *intarr;
    int front;
    int rear;
    int size;
} IntQueue;

void enqueue(IntQueue *q, int val);
int dequeue(IntQueue *q);

int main(int argc, char *argv[]){
    if(argc != 2){
        return 1;
    }
    IntQueue q;
    q.capacity = atoi(argv[1]);
    q.intarr = (int *)malloc(sizeof(int) * q.capacity);
    q.front = 0;
    q.rear = 0;
    q.size = 0;

    enqueue(&q, 1); //rear 0
    enqueue(&q, 2); //rear 1
    enqueue(&q, 3); //rear 2

    // Deque all
    printf("Dequeing all elements\n");
    printf("%i\n", dequeue(&q));
    printf("%i\n", dequeue(&q));
    printf("%i\n", dequeue(&q));

    // Enque again
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);

    // Deque two elements and enque two elements
    printf("Dequeing two elements\n");
    printf("%i\n", dequeue(&q));
    printf("%i\n", dequeue(&q));

    enqueue(&q, 7);
    enqueue(&q, 8);

    printf("Dequeing all elements\n");
    printf("%i\n", dequeue(&q));
    printf("%i\n", dequeue(&q));
    printf("%i\n", dequeue(&q));
}

void enqueue(IntQueue *q, int val){
    if(q->size < q->capacity){
        q->intarr[q->rear] = val;
        q->size++;
        if(q->rear < q->capacity - 1){
            q->rear++;
        } else if(q->front > 0) {
            q->rear = 0;
        }
    } else {
        printf("Queue full, cannot enqueue %i\n", val);
    }
}

int dequeue(IntQueue *q){
    int tmp = -10000000;
    if(q->size > 0){
        tmp = q->intarr[q->front];
        q->size--;
        if(q->size == 0){
            q->front = 0;
            q->rear = 0;
        } else if(q->front < q->capacity - 1){
            q->front++;
        } else {
            q->front = 0;
        }
        if(q->rear == q->capacity - 1){
            q->rear = 0;
        }
    } else {
        printf("Nothing to dequeue\n");
    }
    return tmp;
}
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int capacity;
    int *intarr;
    int top;
} stack;

void push(int val, stack *s);
int pop(stack *s);



int main(int argc, char *argv[]){
    if(argc != 2){
        return 1;
    }
    stack s;
    s.capacity = atoi(argv[1]);
    s.intarr = (int *)malloc(sizeof(int) * s.capacity);
    s.top = -1;

    push(1, &s);
    push(2, &s);
    push(3, &s);
    push(4, &s);
    push(5, &s);
    printf("Popping: \n");
    printf("Popped: %i\n", pop(&s));
    printf("Popped: %i\n", pop(&s));
    printf("Popped: %i\n", pop(&s));
    printf("Popped: %i\n", pop(&s));
    printf("Popped: %i\n", pop(&s));
}

void push(int val, stack *s){
    if(s->top < s->capacity - 1){
        s->top = s->top + 1;
        s->intarr[s->top] = val;
    } else {
        printf("error . . . cannot push\n");
    }
}

int pop(stack *s){
    if(s->top >= 0){
        int tmp = s->intarr[s->top];
        s->top = s->top - 1;
        return tmp;
    } else {
        printf("error . . . stack empty\n");
        return -1000;
    }
}


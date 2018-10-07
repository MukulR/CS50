#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct operandQueue{
    int capacity;
    char* operands;
    int head;
    int tail;
    int size;
} OperandQueue;

typedef struct operatorStack{
    int capacity;
    char* operators;
    int top;
    int size;
} OperatorStack;

void push(OperatorStack *s, char op);
char pop(OperatorStack *s);
bool isOperatorStackEmpty(OperatorStack *s);
char peek(OperatorStack *s);

void enqueue(OperandQueue *q, char op);
char dequeue(OperandQueue *q);
bool isOperandQueueEmpty(OperandQueue *q);

bool isHigherPrecedence(char op1, char op2);
void convertToPostfix(OperatorStack *operatorStack, OperandQueue *operandQueue, char *infix);


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("error");
        return 1;
    }
    OperatorStack operatorStack;
    operatorStack.capacity = strlen(argv[1]);
    operatorStack.top = -1;
    operatorStack.size = 0;
    operatorStack.operators = (char *)malloc(sizeof(char) * operatorStack.capacity);

    OperandQueue operandQueue;
    operandQueue.capacity = strlen(argv[1]);
    operandQueue.head = 0;
    operandQueue.tail = 0;
    operandQueue.size = 0;
    operandQueue.operands = (char *)malloc(sizeof(char) * operandQueue.capacity);

    convertToPostfix(&operatorStack, &operandQueue, argv[1]);
    while(!isOperandQueueEmpty(&operandQueue)){
        char temp = dequeue(&operandQueue);
        printf("%c", temp);
    }
    printf("\n");

    free(operatorStack.operators);
    free(operandQueue.operands);
}

void push(OperatorStack *s, char op){
    if(s->top < s->capacity - 1){
        s->top++;
        s->operators[s->top] = op;
        s->size++;
    } else {
        printf("error . . . cannot push\n");
    }
}

char pop(OperatorStack *s){
    if(s->top >= 0){
        char tmp = s->operators[s->top];
        s->top--;
        s->size--;
        return tmp;
    } else {
        printf("error . . . stack empty\n");
        return '\0';
    }
}

bool isOperatorStackEmpty(OperatorStack *s){
    if(s->size == 0){
        return true;
    }
    return false;
}

char peek(OperatorStack *s){
    return s->operators[s->top];
}

void enqueue(OperandQueue *q, char op){
    if(q->size < q->capacity){
        q->operands[q->tail] = op;
        q->size++;
        if(q->tail < q->capacity - 1){
            q->tail++;
        } else if(q->head > 0) {
            q->tail = 0;
        }
    } else {
        printf("Queue full, cannot enqueue %i\n", op);
    }
}

char dequeue(OperandQueue *q){
    char tmp = '\0';
    if(q->size > 0){
        tmp = q->operands[q->head];
        q->size--;
        if(q->size == 0){
            q->head = 0;
            q->tail = 0;
        } else if(q->head < q->capacity - 1){
            q->head++;
        } else {
            q->head = 0;
        }
        if(q->tail == q->capacity - 1){
            q->tail = 0;
        }
    } else {
        printf("Nothing to dequeue\n");
    }
    return tmp;
}

bool isOperandQueueEmpty(OperandQueue *q){
    if(q->size == 0){
        return true;
    }
    return false;
}

bool isOperator(char c){
    switch(c){
        case '+':
        case '-':
        case '/':
        case '*':
        case ')':
        case '(':
            return true;
        default:
            return false;
    }
}

bool isHigherPrecedence(char op1, char op2){
    if(op2 == '*' && (op1 == '+' || op1 == '-' || op1 == '/')){
        return true;
    } else if(op2 == '/' && (op1 == '+' || op1 == '-')){
        return true;
    } else if(op2 == '-' && op1 == '+') {
        return true;
    }
    return false;
}

void convertToPostfix(OperatorStack *operatorStack, OperandQueue *operandQueue, char *infix){
    int i = 0;
    char c = infix[i];
    while(c != '\0'){
        if(!isOperator(c)){
            enqueue(operandQueue, c);
        } else if(c == '('){
            push(operatorStack, c);
        } else if(c == ')'){
            char temp = pop(operatorStack);
            while(temp != '('){
                enqueue(operandQueue, temp);
                temp = pop(operatorStack);
            }
        } else {
            if (!isOperatorStackEmpty(operatorStack)) {
                char temp = peek(operatorStack);
                while(isHigherPrecedence(c, temp)){
                    temp = pop(operatorStack);
                    enqueue(operandQueue, temp);
                    temp = peek(operatorStack);
                }
            }
            push(operatorStack, c);
        }
        i++;
        c = infix[i];
    }
    while(!isOperatorStackEmpty(operatorStack)){
        char temp = pop(operatorStack);
        enqueue(operandQueue, temp);
    }
}
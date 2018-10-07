#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>


typedef struct OperandStack{
    int capacity;
    char* operands;
    int top;
    int size;
} OperandStack;

void push(OperandStack *s, char op);
char pop(OperandStack *s);
int evaluate(char *postfix);
void operate(char c, int first, int second, OperandStack *operandStack);
double charToDouble(char c);

bool isOperator(char c);



int main(int argc, char *argv[]){
    if(argc != 2){
        return 1;
    }
    int value = evaluate(argv[1]);
    printf("%i\n", value);
}

int evaluate(char *postfix){
    OperandStack operandStack;
    operandStack.capacity = strlen(postfix);
    operandStack.top = -1;
    operandStack.size = 0;
    operandStack.operands = (char *)malloc(sizeof(char) * operandStack.capacity);
    int i = 0;
    char c = postfix[i];
    while(c != '\0'){
        if(!isOperator(c)){
            double d = charToDouble(c);
            push(&operandStack, d);
        } else {
            double second = pop(&operandStack);
            double first = pop(&operandStack);
            operate(c, first, second, &operandStack);
        }
        i++;
        c = postfix[i];
    }
    return pop(&operandStack);
}

void push(OperandStack *s, char op){
    if(s->top < s->capacity - 1){
        s->top++;
        s->operands[s->top] = op;
        s->size++;
    } else {
        printf("error . . . cannot push\n");
    }
}

char pop(OperandStack *s){
    if(s->top >= 0){
        char tmp = s->operands[s->top];
        s->top--;
        s->size--;
        return tmp;
    } else {
        printf("error . . . stack empty\n");
        return '\0';
    }
}


void operate(char c, int first, int second, OperandStack *operandStack){
    switch(c){
        case '+':
            push(operandStack, first + second);
            break;
        case '-':
            push(operandStack, first - second);
            break;
        case '*':
            push(operandStack, first * second);
            break;
        case '/':
            push(operandStack, first / second);
            break;
    }
}

double charToDouble(char c){
    double value = c;
    return value - 48;
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
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

struct IntNode {
    int data;
    struct IntNode *next;
};

struct IntNode *reverse(struct IntNode *head);
void printNodeData(struct IntNode *first);
int find(struct IntNode *head, int intToFind);

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Expected 1 argument\n");
        return 1;
    }

    struct IntNode *head = NULL;
    struct IntNode *prev = NULL;
    struct IntNode *n = NULL;
    int nodes = atoi(argv[1]);
    for(int i = 0; i < nodes; i++){
        n = (struct IntNode *)malloc(sizeof(struct IntNode));
        n->data = i;
        if(head == NULL){
            head = n;
        } else {
            prev->next = n;
        }
        prev = n;
    }
    printNodeData(head);

    int num = atoi(argv[2]);
    find(head, num);
    head = reverse(head);
    printf("reversed nodes\n");
    printNodeData(head);
    struct IntNode *temp = head;
    while(temp != NULL){
        struct IntNode *nodeToFree = temp;
        temp = temp->next;
        free(nodeToFree);
    }

}

void printNodeData(struct IntNode *first) {
    while (first != NULL) {
        printf("%i\n", first->data);
        first = first->next;
    }
}

struct IntNode *reverse(struct IntNode *head){
    if(head == NULL || head->next == NULL){
        return head;
    }

    struct IntNode *prev = head;
    head = head->next;
    prev->next = NULL;
    struct IntNode *n = head->next;
    head->next = prev;


    while(n != NULL){
        prev = head;
        head = n;
        n = head->next;
        head->next = prev;
    }
    return head;
}


int find(struct IntNode *head, int intToFind){
    int count = 0;
    while(head != NULL){
        int currdata = head->data;
        if(currdata == intToFind){
            printf("data belongs to %i index node.\n", count);
            return 1;
        }
        head = head->next;
        count++;
    }
    printf("not found\n");
    return 2;
}
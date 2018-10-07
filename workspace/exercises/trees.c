#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;


void insert(struct TreeNode* treeNode, int value);
struct TreeNode *makeNewNode(int val);
void find(struct TreeNode* root, int valToFind);

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("error\n");
        return 1;
    }

    int val = atoi(argv[1]);
    struct TreeNode *root = makeNewNode(val);
    root->left = NULL;
    root->right = NULL;
    int upper = 50;
    int lower = 0;
    int arr[5];
    for(int i = 0; i < 5; i++){
        int num = (rand() % (upper - lower + 1)) + lower;
        insert(root, num);
        arr[i] = num;
    }
    for(int i = 0; i < 5; i++){
        find(root, arr[i]);
    }
    find(root, 500);
}


//function inserts data into tree
void insert(struct TreeNode* root, int value){
      struct TreeNode *currentNode = root;
    if(currentNode->data == value){
        return;
    }
    while(value < currentNode->data){
        if(currentNode->left == NULL){
            struct TreeNode *newNode = makeNewNode(value);
            currentNode->left = newNode;
            return;
        } else {
            currentNode = currentNode->left;
        }
    }
    while(value > currentNode->data){
        if(currentNode->right == NULL){
            struct TreeNode *newNode = makeNewNode(value);
            currentNode->right = newNode;
            return;
        } else {
            currentNode = currentNode->right;
        }
    }
}

//function allocates memory for each new node created when inserting data
struct TreeNode *makeNewNode(int val){
    struct TreeNode *temp = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// function finds data in a tree
void find(struct TreeNode* root, int valToFind){
    struct TreeNode *currentNode = root;
    bool valfound = false;
    while(currentNode != NULL){
        if(currentNode->data == valToFind){
            valfound = true;
            break;
        } else if(valToFind > currentNode->data){
            currentNode = currentNode->right;
        } else {
            currentNode = currentNode->left;
        }
    }

    if(valfound == true){
        printf("Found %i!\n", valToFind);
    } else {
        printf("Could not find %i\n", valToFind);
    }
}
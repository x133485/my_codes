#include"function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Node* createNode(char *key,char *description){  //返回一个node类型的指针，createNode

    if(key ==NULL || strlen(key) == 0){
        printf("Error: Key can not be empty !\n");
        return NULL;
    }else if(description ==NULL || strlen(description) == 0){
        printf("Error: Description can not be empty!\n");
        return NULL;
    }else{
        Node* newNode = (Node*) malloc(sizeof(Node));

        if (!newNode) {
            printf("Error: Memory allocation failed.\n");
            return NULL;
        }
    
        strncpy(newNode->key, key, sizeof(newNode->key) - 1);
        newNode->key[sizeof(newNode->key) - 1] = '\0';
    
    
        strncpy(newNode->description, description, sizeof(newNode->description) - 1);
        newNode->description[sizeof(newNode->description) - 1] = '\0';
    
        newNode->left = NULL;
        newNode->right = NULL;
    
        return newNode;
    }



}

void printNode(Node *node){
    if (node ==NULL){
        printf(" The node is NULL.\n");
    }else{
        printf("The key of the node is :%s.\n", node->key);
        printf("The description of the node is :%s.\n", node->description);
    }  
}

Tree* createTree(){
    Tree* newTree = (Tree*)malloc(sizeof(Tree));
    newTree->root = NULL;

    return newTree;
}

int treeEmpty(Tree *tree){
    if(tree ==NULL || tree->root ==NULL){
        return 1;
    }else{
        return 0;
    }
}

void insertNode(Node *node, Tree *tree){
    if(treeEmpty(tree)){
    tree->root = node;
    printf("The node %s had been inserted as root node successfully!\n",node->key);
    return;  //这里假如不添加会怎么样？
    }

    Node *current_node = tree->root;
    while (current_node !=NULL)
    {
        if (strcmp(node->key,current_node->key)>0){
            if(current_node->right == NULL){
                current_node->right = node;
                printf("The node %s had been inserted to right of %s!\n",node->key,current_node->key);
                return;
            }
            current_node = current_node->right;
}
        if (strcmp(node->key,current_node->key)<0){
            if(current_node->left == NULL){
                current_node->left = node;
                printf("The node %s had been inserted to left of %s!\n",node->key,current_node->key);
                return;
            }
            current_node = current_node->left;
        }
        if(strcmp(node->key,current_node->key)==0){
            printf("The node already exists!\n");
            free(node);
            return; // 这里插入防止二次循环。
        }
        
    }
    
    
   
}

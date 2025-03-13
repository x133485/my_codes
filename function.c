#include"function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Node* createNode(char *key,char *description){  //返回一个node类型的指针，createNode
    Node* newNode = (Node*) malloc(sizeof(Node));

    if(key ==NULL){
        printf("Please enter the value of key!\n");
        scanf(" %29s",newNode->key);
    }else{
        strncpy(newNode->key ,key ,sizeof(newNode->key)-1);  //将输入过来的内容复制到节点上，这一步可以防止溢出
        //newNode->key[-1] = '\0';  不可以这样，因为合法的索引范围是0-29
        newNode->key[sizeof(newNode->key)-1] = '\0';
    }

    if(description ==NULL){
        printf("Please enter the content of description!\n");
        scanf(" %199s",newNode->description);
    }else{
        strncpy(newNode->description ,description ,sizeof(newNode->description)-1);  //将输入过来的内容复制到节点上，这一步可以防止溢出
        newNode->description[sizeof(newNode->description)-1] = '\0';
    }

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;

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
    return;  //这里假如不添加会怎么样？
    }

    Node *current_node = tree->root;
    while (current_node !=NULL)
    {
        if (strcmp(node->key,current_node->key)>0){
            if(current_node->right == NULL){
                current_node->right = node;
            }
            current_node = current_node->right;

        }else if (strcmp(node->key,current_node->key)<0){
            if(current_node->left == NULL){
                current_node->left = node;
            }
            current_node = current_node->left;

        }else{
            printf("The node already exists!\n");
            free(node);
        }
        
    }
    
    
   
}

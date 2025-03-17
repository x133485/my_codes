#include"function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Node* createNode(char *key,char *description){  //返回一个node类型的指针，createNode

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
    printf("The key %s had been inserted as root node successfully!\n",node->key);
    return;  //这里假如不添加会怎么样？
    }

    Node *current_node = tree->root;
    while (current_node !=NULL)
    {
        if (strcmp(node->key,current_node->key)>0){
            if(current_node->right == NULL){
                current_node->right = node;
                printf("The key %s had been inserted to right of %s!\n",node->key,current_node->key);
                return;
            }
            current_node = current_node->right;
}
        if (strcmp(node->key,current_node->key)<0){
            if(current_node->left == NULL){
                current_node->left = node;
                printf("The key %s had been inserted to left of %s!\n",node->key,current_node->key);
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

int countNodes(Node* root){
    if (root ==NULL){
        return 0;
    }else{
        return 1+ countNodes(root->left) + countNodes(root->right);
    }
}

void inorderPrint(Node *root,int n, int* count){
    
    if(root ==NULL || *count > n ){
        return;
    }
    inorderPrint(root->left, n, count);

    if (*count < n) {
        printf("%s ", root->key);
        (*count)++;
    }

    inorderPrint(root->right, n, count);
}

Node* search(Node *root, char *key){
    if (root ==NULL || strcmp(root->key, key) == 0){
        return root;
    }

    Node * result = NULL;

    if (strcmp(key,root->key)>0){
        result = search(root->right,key);
    }else if (strcmp(key,root->key)<0){
        result = search(root->left,key);
    }

    return result;

}

Node *delete(Node *root, char *key){  //返回删除节点后子树的根节点
    if (root ==NULL){
        return NULL;
    }
    //写终止条件
    if (strcmp(root->key, key) == 0){
        if(root->left ==NULL && root->right == NULL){
            free(root);
            return NULL;
        }else if(root->left !=NULL && root->right == NULL){
            free(root);
            return root->left;
        }else if(root->left ==NULL && root->right != NULL){
            free(root);
            return root->right;
        }else{
            Node *cur = root->right;

            while (cur->left !=NULL){
                cur = cur->left;
            }
            strcpy(root->key,cur->key); //把中序后继节点替换该目标节点
            strcpy(root->description,cur->description);

            //之前的只是复制了，原先节点还存在于二叉树，因此要进行删除
            root->right = delete(root->right,cur->key);  

        }
        return root;
    }
    //递归条件
    if(strcmp(key ,root->key)<0){
        root->left = delete(root->left, key);
    }else if (strcmp(key ,root->key)>0){
        root->right = delete(root->right, key);
    }

    return root;

}

void loadTextFile(char* filename){
    FILE *file = fopen(filename,"r");
    if (!file){
        printf("File can not be found.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        // 移除换行符
        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) == 0) {
            printf("Warning: Empty line skipped.\n");
            continue;
        }

        // 检查是否以 "." 结尾
        if (line[strlen(line) - 1] != '.') {
            printf("Invalid format: Line does not end with a dot.\n");
            continue;
        }

        // 查找冒号
        char *colonPos = strchr(line, ':');
        if (!colonPos) {
            printf("Invalid format: Missing colon in line.\n");
            continue;
        }

        *colonPos = '\0';
        char *key = line;
        char *description = colonPos + 1;

        if (strlen(key) == 0 || strlen(description) == 0) {
            printf("Invalid format: Key or description is empty.\n");
            continue;
        }

        Node *newNode = createNode(key, description);
        if (!newNode) {
            printf("Memory allocation failed.\n");
            continue;
        }

        printf("Key: %s, Description: %s\n", newNode->key, newNode->description);
        free(newNode);

    }
    fclose(file);
}

void preorderWrite(Node *node,FILE *file){
    if (node == NULL){
        return;
    }
    fprintf(file,"%s:%s.\n",node->key,node->description);
    preorderWrite(node->left,file);
    preorderWrite(node->right,file);
    
}

void storeTextFile(Node* root,char *filename){
    FILE *file = fopen(filename,"w");
    if (file == NULL){
        printf("Can't open the file.\n");
        return;
    }

    preorderWrite(root,file);
    fclose(file);
    
}
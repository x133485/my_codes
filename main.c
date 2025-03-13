#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"function.h"

int main(){

    Tree *trees[10];
    Node *nodes[100];
    int treeCount = 0;
    int nodeCount = 0;

    while (1)
    {   
        int choice;
        printf("Welcome to the System !\n");
        printf("Input 0 to quit.\n");
        printf("Input 1 for creating a new node:\n");
        printf("Input 2 for printing the existing node:\n");
        printf("Input 3 for creating a new tree:\n");
        printf("Input 4 for checking the tree empty or not:\n");
        printf("Input 5 for inserting the node to existing tree:\n");

        printf("Please enter the number:\n");
        scanf(" %d",&choice);
        getchar();

        if(choice == 1){

            char key[30];
            char description[200];

            printf("Please input the key:\n");
            fgets(key,29,stdin);
            key[strcspn(key, "\n")] = '\0';

            printf("Please input the description:\n");
            fgets(description,199,stdin);
            description[strcspn(description, "\n")] = '\0';

            nodes[nodeCount] = createNode(key,description);
            printf("Node create successfully!\n");
            printf("============================\n");
            nodeCount++;

        }else if (choice ==2)
        {
            if (nodeCount == 0){
                printf("Please add a node first!\n");
            }else{
                for(int i=0;i<nodeCount;i++){
                    printf("The node %d:\n",i+1);
                    printf("    Key:%s\n",nodes[i]->key);
                    printf("    Description:%s\n",nodes[i]->description);
                }
            }

            printf("============================\n");
        }else if (choice ==0){
            printf("Good bye \n");
            break;
        }
        
    }
    

    return 0;
}
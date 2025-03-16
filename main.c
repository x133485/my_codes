#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"function.h"

int main(){

    Tree *trees[10];
    Node *nodes[100];
    int treeCount = 0;
    int nodeCount = 0;

    printf("Welcome to the System !\n");

    while (1)
    {   
        int choice;
        
        printf("\n");

        printf("Input 0 to quit.\n");
        printf("Input 1 for creating a new node:\n");
        printf("Input 2 for printing the existing node:\n");
        printf("Input 3 for creating a new tree:\n");
        printf("Input 4 for checking the tree empty or not:\n");
        printf("Input 5 for inserting the node to existing tree:\n");
        printf("Input 6 performing inorder traversal of binary tree:\n");
        printf("Input 7 for search a node with given key:\n");
        printf("Input 8 for deleting a node.\n");

        printf("Please enter the number:\n");
        scanf(" %d",&choice);
        getchar();

        if(choice == 1){

            char key[30];
            char description[200];

            printf("Please input the key(Max 29 characters):\n");
            fgets(key,sizeof(key),stdin); //fgets第二个参数是缓冲区大小的意思
            
            if (strchr(key, '\n') == NULL) {  //检查是否有换行符
                printf("Error: Key is too long (max 29 characters allowed).\n");
                clearInputBuffer();
                continue;
            } else {
                key[strcspn(key, "\n")] = '\0'; // 移除换行符
            }
            
            //检查是否为空
            if (strlen(key) == 0) {
                printf("Error: Key cannot be empty!\n");
                continue; 
            }            
            
            printf("Please input the description (max 199 characters):\n");
            fgets(description, sizeof(description), stdin);

            if (strchr(description, '\n') == NULL) {
                printf("Error: Description is too long (max 199 characters allowed).\n");
                clearInputBuffer();
                continue;
            } else {
                description[strcspn(description, "\n")] = '\0';
                }

            if (strlen(description) == 0) {
                printf("Error: Description cannot be empty!\n");
                continue; 
            }   

            int duplicate = 0;
            for(int i = 0; i< nodeCount;i++){
                if(strcmp(nodes[i]->key,key) == 0){
                    duplicate = 1;
                    break;
                }
            }

            if (duplicate){
                printf("Error: the node had already exists. Create the key failed!\n");
                printf("Exist key: %s\n",key);
                printf("============================\n");
            }else{
                nodes[nodeCount] = createNode(key,description);
                printf("Node %d create successfully!\n",nodeCount+1);
                printf("============================\n");
                nodeCount++;
            }
            

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
        }else if(choice == 3){
            trees[treeCount] = createTree();
            treeCount++;
            printf("New tree %d created successfully!\n",treeCount);
            printf("============================\n");
        }else if (choice ==4){
            if(treeCount ==0){
                printf("Please create a tree first before checking.\n");
                printf("============================\n");
            }else{
                int num_tree;

                printf("Existing trees number %d.\n",treeCount);
                printf("Select which tree you want to check. Select from 1 to %d.\n",treeCount);
                scanf(" %d",&num_tree);

                if(num_tree < 1 || num_tree >treeCount){
                    printf("The number you input is out of the scope, please select from 1-%d.\n",treeCount);
                }else{
                    if(treeEmpty(trees[num_tree-1])){
                        printf("The tree you selected is empty!\n");
                        printf("============================\n");
                    }else{
                        printf("The tree is not empty.\n");
                        printf("============================\n");
                    }
                }
            }
        }else if (choice == 5){
            int tree_num;
            int node_num;
            if(treeCount ==0 ||nodeCount ==0){
                printf("Please make sure you had created tree and a node first.\n");

            }else{
                printf("Which tree num  you want to insert? Select only one number from 1-%d.\n",treeCount);
                scanf(" %d",&tree_num);
                printf("And which node num you want to insert. Select node number from 1-%d.\n",nodeCount);

                for(int i =0;i<nodeCount;i++){
                    printf("Node %d, key: %s\n",i+1,nodes[i]->key);
                }

                scanf(" %d",&node_num);
                if (0 <tree_num && tree_num <=treeCount && 0<node_num && node_num<=nodeCount){
                    //insertNode(nodes[node_num-1],trees[tree_num-1]);  This will make tree influence each other

                    Node *copyNode = createNode(nodes[node_num-1]->key, nodes[node_num-1]->description);
                    if (copyNode != NULL) {
                        insertNode(copyNode, trees[tree_num-1]);
                    } else {
                        printf("Failed to create a copy of the node.\n");
                    }
                }else{
                    printf("The tree num you selected or the node num you selected is out of bound.\n");
                }
                
            }
        }else if (choice==6){
            int num;
            int tree_num;
            int count =0;

            printf("Select which tree you want to traversal:\n");
            printf("Select from 1-%d\n",treeCount);
            scanf(" %d",&tree_num);
            
            if(0<tree_num && tree_num<treeCount+1){
                int total_nodes = countNodes(trees[tree_num-1]->root);
                printf("How many nodes you want to traversal? Select from 1-%d.\n",total_nodes);
                scanf(" %d",&num);
                if(num>0 && num<total_nodes+1){
                    inorderPrint(trees[tree_num-1]->root,num, &count);
                    printf("\n======================\n");
                }else{
                    printf("The node num you select is out of bound.\n");
                }

                continue;
                
            }else{
                printf("The tree num you select is out of bound, please select again.\n");
                continue;
            }
            
        }else if(choice ==7){
            char target[30];
            int num;
            Node *node;

            printf("Input the key which you want to query:\n");
            fgets(target,sizeof(target),stdin);
            target[strcspn(target, "\n")] = '\0';

            printf("Select which tree you want to query 1-%d:\n",treeCount);
            scanf("%d",&num);
            if (num >0 && num <treeCount+1){
                node = search(trees[num-1]->root,target);
                if (node !=NULL){
                    printf("The node you want to query:%s.\n",node->key);
                    printf("The description is :%s.\n",node->description);
                    printf("============================\n");
                }else{
                    printf("Cannot find the key in the given tree.\n");
                    printf("============================\n");
                }                
            }else{
                printf("Please enter correct num.\n");

            }
        }else if(choice  ==8){
            int tree_num;
            char key[30];
            Node *node;

            printf("The node was on which tree? 1-%d:\n",treeCount);
            scanf(" %d",&tree_num);
            if (tree_num >0 && tree_num <treeCount+1){
                printf("Input the key you want to delete:\n");
                scanf(" %s",key);
                node = search(trees[tree_num-1]->root,key);

                if (node !=NULL){
                    printf("The node you want to delete: %s.\n",node->key);
                    printf("The description is : %s.\n",node->description);

                    trees[tree_num-1]->root =  delete(trees[tree_num-1]->root,key);
                    printf("Delete selected node successfully!\n");
                }else{
                    printf("Cannot  find the key you want to delete.\n");
                }

            }
        }              
        
    }
    

    return 0;
}
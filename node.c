#include "node.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//defining the createNode function 
// it returns a dynamically allocated pointer to the node that is created (here it is called head)

Node* createNode(int emp_id, char* n, int Age, float sal, Node* next_node){
    Node* head = (Node*)malloc( sizeof(Node));
    
    head->id=emp_id;
    head->name = strdup(n); 
    head->age=Age;
    head->salary=sal;
    head->next=next_node;
    
    return head;
}


// simple function to print the entire node 

void print(Node* node){
    printf("details of emp with employee id : %d\n", node->id);
    printf("name : %s\n", node->name);
    printf("age : %d\n", node->age);
    printf("salary : %.2f\n\n", node->salary);
}
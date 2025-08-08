



// structure of each node of the linked list
// typedefining it to be called "Node" for simplicity

typedef struct Node{
    int id;
    char *name;
    int age;
    float salary;
    struct Node* next;
    
}Node;


// below functions are define in the "node.c" file

Node* createNode(int emp_id, char* n, int Age, float sal, Node* next_node);

void print(Node* node);

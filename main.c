#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "node.h"



// all necessary function declarations

int Remove(Node** head, Node** tail, int emp_id);
void print_info(Node** head, int emp_id);
void remove_from_file(int emp_id, FILE* fptr);

void file_to_ll(Node** head, Node** tail, FILE* fptr);  //  generates the linked list from the
// empt.txt file so that all the operations then on can be done on the linked list for ease


int validate(int emp_id,char* n,int Age,float sal, Node** tail);
// input validation, to make sure irrelevant info or garbage info is not given as input
// returns 1 for a valid info and 0 for invalid entry

int main(int argc, char **argv){
    Node* head=NULL;  // first node
    Node* tail=NULL;  // last node
	FILE* fptr=NULL;
    
    fptr=fopen("emp.txt", "r+");
    if(fptr==NULL){
        printf("error fetching the directory\n");
        return 1;
    }
    
    file_to_ll(&head,&tail,fptr); // get the entire file into a linked list asap
    
    
    
    while(1){
        printf("you can exit: press -1\n");
        printf("to get the entire list of employees: press 1 \n");
        printf("to add employee: press 2 \n");
        printf("to remove employee: press 3 \n");
        printf("to print a specific employee's info: press 4 \n");
        int command; scanf("%d", &command); if(command==-1)break;
        
        if(command==1){
            
            printf("printing all employess info\n\n");
            Node* temp=head;
            while(temp){
                print(temp);
                temp=temp->next;
            }
        }
        
        
        
        // add employee
        else if(command==2){
            
            int emp_id; char n[100]; int Age; float sal;
            while(1){
                printf("give details:\n");
                printf("id: ");
                scanf("%d", &emp_id);
                printf("name: ");
                scanf(" %[^\n]", n);
                
                
                printf("Age: ");
                scanf("%d", &Age);
                printf("salary: ");
                scanf("%f", &sal);
                
                if(validate(emp_id,n,Age,sal, &tail)==1)break;
                else printf("invalid entry.. try again\n");
            }
            
            Node* temp=createNode(emp_id,n,Age,sal,NULL);
            
            if (tail) {
                tail->next = temp;
                tail = temp;
            } 
            else head = tail = temp;
            fseek(fptr, 0, SEEK_END);
            fprintf(fptr, "%d;%s;%d;%.2f\n", emp_id, n, Age, sal);
            rewind(fptr);
        }
        
        
        
        else if(command==3){
            // remove an employee
            printf("give the id of the employee you want to erase:\n");
            int emp_id;
            scanf("%d", &emp_id);
            
            
            // no head means empty list and empty file 
            if(!head){
                printf("no employees in directory\n");
                continue;
            }
            
            // invalid id was given
            if(Remove(&head, &tail, emp_id) == 0){
                printf("no such employee exists, give a valid employee id please..\n");
                continue;
            }
            
            // else successful deletion
            else{
                printf("employee erased from directory\n");
                remove_from_file(emp_id,fptr);
            }
        }
        
        
        else if(command==4){
            // print specific employee
            printf("give the id of the employee you want to print:\n");
            int emp_id;
            scanf("%d", &emp_id);
            print_info(&head, emp_id);
        }
    }


    
    fclose(fptr);
    
    
	return 0;
}


int Remove(Node** head, Node** tail, int emp_id) {
    if (*head == NULL) return 0;

    Node* temp = *head;

    // Case 1: Deleting head
    if (temp->id == emp_id) {
        *head = temp->next;
        if (*head == NULL) {
            // List became empty
            *tail = NULL;
        }
        free(temp);
        return 1;
    }

    // Case 2: Deleting from middle or end
    while (temp->next && temp->next->id != emp_id) {
        temp = temp->next;
    }

    if (!temp->next) return 0; // Not found

    Node* del_one = temp->next;  // del_one points to the node that needs to be deleted
    temp->next = temp->next->next;

    if (del_one == *tail) {
        *tail = temp; // Update tail if deleting last node
    }

    free(del_one);
    return 1;
}




// find the node and print the deatils
void print_info(Node** head, int emp_id){
    Node* temp=(*head);
    
    while(temp){
        if(temp->id==emp_id)break;
        temp=temp->next;
    }
    // if temp points to NULL, no such employee exits
    if(!temp){
        printf("no employee with that id\n");
        return;
    }
     
    // print the employee, using the predefine print function in node.c
    print(temp);
}





// deletes entry from the file, using '#'
// Function to mark an employee's record as deleted in the file by prefixing the line with '#'
void remove_from_file(int emp_id, FILE* fptr) {
    char line[256];         // Buffer to read each line from the file
    rewind(fptr);           // Go to the beginning of the file

    while (1) {
        long pos = ftell(fptr);  // Store current file position to later overwrite if needed

        // Read a line from the file; break if end of file
        if (fgets(line, sizeof(line), fptr) == NULL) break;

        // Skip lines that are already marked as deleted
        if (line[0] == '#') continue;

        int id;
        char num_buf[100];  // Temporary buffer to hold the ID string
        int num_i = 0;
        int i = 0;

        // Extract the ID from the beginning of the line (up to the first semicolon)
        while (line[i] != ';' && line[i] != '\0') {
            num_buf[num_i++] = line[i++];
        }
        num_buf[num_i] = '\0';   // Null-terminate the string
        id = atoi(num_buf);      // Convert extracted string to integer

        // If the ID matches the one to be removed
        if (id == emp_id) {
            fseek(fptr, pos, SEEK_SET);  // Seek back to the beginning of this line
            fputc('#', fptr);            // Overwrite the first character with '#'
            fflush(fptr);                // Ensure changes are flushed to disk
            break;                       // Done — exit the loop
        }
    }
}




// function to validate user provided input
int validate(int emp_id,char* n,int Age,float sal, Node **tail){
    // for emp_id validation we need to make sure it is 
    //one greater than the last employee's id in the list
    
    if((*tail)==NULL){
        if(emp_id!=1)return 0;
    }
    
    if(emp_id != ((*tail)->id)+1 )return 0;
    
    
    // Age must be between 20 and 80
    
    if(Age<20 || Age >80)return 0;
    
    
    // name must not be empty and must only contain upper and lower case alphabets
    
    if(strlen(n)==0)return 0;
    
    for(int i=0; i<strlen(n); i++){
        if( (n[i]>='A' && n[i]<='Z') || (n[i]>='a' && n[i]<='z') || n[i]==' ')continue;
        else return 0;
    }
    
    
    // salary must be between 100 and 10000000
    
    if(sal<100.0 || sal>10000000.0)return 0;
    
    
    return 1;
    
}











// Function to read employee data from a file and build a linked list

void file_to_ll(Node** head, Node** tail, FILE* fptr) {
    char line[256];  // Buffer to store each line from the file

    // Read each line from the file
    while (fgets(line, sizeof(line), fptr)) {
        // Skip lines marked as deleted
        if (line[0] == '#') continue;

        int id, Age;
        float sal;
        char num_buf[100]; int num_i = 0;          // Buffer for numeric fields
        char name_buf[100]; int name_i = 0;        // Buffer for name field
        int i = 0, field = 0;                      

        // Parse the line character by character until end of line
        while (line[i] != '\0' && line[i] != '\n') {
            if (field == 0) { // Parsing ID
                if (line[i] == ';') {
                    num_buf[num_i] = '\0';         
                    id = atoi(num_buf);            
                    field++;                       
                    num_i = 0;                     
                } else {
                    num_buf[num_i++] = line[i];    // Accumulate characters
                }
            } else if (field == 1) { // Parsing Name
                if (line[i] == ';') {
                    name_buf[name_i] = '\0';      
                    field++;                       // Move to next field
                } else {
                    name_buf[name_i++] = line[i];  
                }
            } else if (field == 2) { // Parsing Age
                if (line[i] == ';') {
                    num_buf[num_i] = '\0';        
                    Age = atoi(num_buf);           // Convert to integer
                    field++;                      
                    num_i = 0;                     
                } else {
                    num_buf[num_i++] = line[i];   
                }
            } else if (field == 3) {                // Parsing Salary
                num_buf[num_i++] = line[i];        
            }
            i++;
        }

        // Final salary conversion after loop
        
        num_buf[num_i] = '\0';                     
        sal = atof(num_buf);                       // Convert to float

        // Create a new node with the parsed data
        Node* temp = createNode(id, name_buf, Age, sal, NULL);

        // Append the node to the linked list
        if (*head == NULL) {
            *head = temp;                          // First node in the list
            *tail = temp;
        } else {
            (*tail)->next = temp;                  // Append to tail
            *tail = temp;                          // Update tail
        }
    }
}

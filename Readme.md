# Employee Management using File Handling and Linked List


We are storing the details in files so that the details can be persistent and a linked list is being used so that add and remove 
operations can be faster. 

The file is named emp.txt

The structure of a node is same as each line entry in the file



-------------------------------------------------------------------------------------------------------------------------------------




# Node.h ::: Defines a structure representing an employee record stored in a linked list node. Each node contains:

int id — The employee's ID.

char* name — A pointer to a dynamically allocated string containing the employee's name.

int age — The employee's age.

float salary — The employee's salary.

Node* next — A pointer to the next node in the linked list.

This structure forms the building block of a singly linked list to store employee data.





## Node* createNode(int emp_id, char* n, int Age, float sal, Node* next_node);
Purpose:
Creates a new Node dynamically with the given employee details.

Parameters are same as each entry, NULL is passed for next_node initially.






## void print(Node* node);
Purpose:
Prints the contents of a node to standard output in a human-readable format.

Parameter:

node — A pointer to the Node whose data will be printed.

Output Example:

ID: 101
Name: Alice
Age: 30
Salary: 45000.00






-------------------------------------------------------------------------------------------------------------------------------------






# node.c :::: Implementation of Node Functions


Both createNode and print functions are defined here that were declared in the node.h file

createNode function return a pointer to the node called head.









-------------------------------------------------------------------------------------------------------------------------------------





# emp.txt :::: Employee Data File
This file contains persistent employee records used by the program. 
Each line in the file represents an employee.

## File Structure
Each line follows this format:

## id;name;age;salary

id — Unique integer employee ID

name — Employee's full name (can include spaces)

age — Integer age

salary — Float salary (with or without decimal places)

1;Asit Vats;22;30000
2;Ravi Kumar;25;45000

These entries are used to initialize the linked list at runtime (i.e., on program startup) and 
may also be updated or rewritten when changes are made in memory (e.g., adding or removing a node).

Some lines might start with hashtag, that is to signify that those entries have been deleted ( or that employee has left the 
organisation)

example
'#'1;ansh;23;100000.00

-------------------------------------------------------------------------------------------------------------------------------------


# main.c :::: Everything starts here (main logic is written here)


This file contains the main logic for the Employee Management System. 
It interacts with the user, handles all command inputs, and coordinates the reading from and writing to the file (emp.txt) 
and the in-memory linked list.

## Key Responsibilities of main.c:

### Load employee data from the file (emp.txt) into a linked list on startup.

### Provide a menu-based interface to:

### View all employees

### Add a new employee

### Remove an employee

### Print details of a specific employee

### Persist changes back to the file

### Ensure efficient in-memory operations using a singly linked list






## file_to_ll(Node** head, Node** tail, FILE* fptr);
Purpose:
Reads each line from the file emp.txt and creates a node for each employee, linking them together to form the initial linked list.

Details:

Skips lines starting with '#' (those are marked as deleted).

Parses each field from the line: id;name;age;salary.

Appends the created node to the end of the list using the tail pointer.




## int Remove(Node** head, Node** tail, int emp_id);
Purpose:
Removes a node with the specified employee ID from the linked list.

Details:

Handles removal from head, middle, and end of the list.

Updates tail if the last node is removed.

Frees dynamically allocated memory for both the node and its name.

Returns:

1 if a node was removed successfully.

0 if no matching node was found.





## void print_info(Node** head, int emp_id);
Purpose:
Searches the list for an employee with the specified ID and prints their details using the print() function.

Details:

Prints "no employee with that id" if not found.





## void remove_from_file(int emp_id, FILE* fptr);
Purpose:
Marks an employee entry as deleted in the file (emp.txt) by replacing the first character of that line with #.

Details:

Uses ftell() to remember the line’s position.

Uses fseek() and fputc() to overwrite the first character.

Keeps the line structure intact for consistency.





## int validate(int emp_id, char* n, int Age, float sal, Node** tail);
Purpose:
Validates user input before creating and adding a new employee node to the linked list and writing it to the file.

Ensures that all fields (emp_id, name, age, salary) meet strict data integrity constraints to prevent malformed or incorrect records.

Details:

### Employee ID (emp_id) Validation:

If the list is empty, the first emp_id must be 1.

Otherwise, the new emp_id must be exactly one greater than the current last employee's ID.

This enforces sequential and unique IDs.

### Age Validation:

Acceptable range is between 20 and 80 (inclusive).

Prevents unrealistic ages for employees.

### Name (n) Validation:

Must not be empty.

Can only contain uppercase and lowercase alphabetic characters and spaces.

Disallows numbers, special characters, and other invalid symbols.

### Salary Validation:

Acceptable range is from 100.00 to 10,000,000.00.

Ensures that salaries are within realistic bounds.

### Return Value:

Returns 1 if all validations pass (i.e., the input is valid).

Returns 0 if any validation check fails.





## int main()
Purpose:
Entry point of the program. Handles user interaction via a menu system.

Main Tasks:

Opens the emp.txt file in read/update mode.

Loads all valid employee data into a linked list using file_to_ll().

Displays a menu in a loop:

1 → Print all employees

2 → Add a new employee

3 → Remove an employee (from list and file)

4 → Print a specific employee’s info

-1 → Exit the program

On adding a new employee:

Collects data from the user

Adds a new node to the list

Appends the same to the file

On removal:

Deletes from linked list using Remove()

Marks the corresponding line in file using remove_from_file()

Closes the file and frees memory before exit.

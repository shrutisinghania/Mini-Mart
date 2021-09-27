#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node                                                             // Link list node
{ 
    int itemCode;
    char description[500];
    int quantity;
    int price;
    struct Node *next;                                                  // declare next of node
};

struct Node* node(int new_itemCode, char desc[500], int q, int p)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));       // allocate node 
    node->itemCode = new_itemCode;                                       // put in the data 
    strcpy(node->description, desc);
    node->quantity = q;
    node->price = p;
    node->next = NULL;
    return node;
}

void insertNode(struct Node **head, struct Node *node)          // Function to insert a new_node in a list
{
    struct Node *current;
    if (*head == NULL || (*head)->itemCode >= node->itemCode)   // Special case for the head end 
    {
        node->next = *head;
        *head = node;
    }
    else                                                        // Locate the node before the point of insertion
    {
        current = *head;
        while (current->next != NULL && current->next->itemCode < node->itemCode)
        {
            current = current->next;                            // Traverse the next node
        }
        node->next = current->next;
        current->next = node;
    }
}

void edit(struct Node* node, char desc[500], int q, int p){     // Edits the given node info
    strcpy(node->description, desc);                            // Update description
    node->quantity = q;                                         // Update quantity
    node->price = p;                                            // Update price
}

void printList(struct Node* head)                               // Prints the linked list
{
    struct Node* temp = head;
    while (temp != NULL) {
        printf("\nItemCode = %d  ", temp->itemCode);            // Print itemCode
        printf("\nDescription = %s  ", temp->description);      // Print description
        printf("\nQuantity = %d  ", temp->quantity);            // Print quantity
        printf("\nPrice = %d  \n\n", temp->price);              // Print price
        temp = temp->next;
    }
}

struct Node* find(struct Node* head, int new_itemCode)           // Checks whether the new_itemCode is present in linked list
{
    struct Node* current = head;                                // Initialize current
    while (current != NULL)
    {
        if (current->itemCode == new_itemCode)
            return current;                                     // Return current if present
        current = current->next;
    }
    return NULL;                                                // Return NULL if not present
}

void del(struct Node** head, int i)
{
    struct Node *temp = *head;                                  // Store head node
    struct Node *prev = NULL;                           
    if (temp != NULL && temp->itemCode == i) {                  // If head node itself holds the key to be deleted
        *head = temp->next;                                     // Changed head
        free(temp);                                             // free old head
        printf("\nItem deleted successfully");
        return;
    }
    while (temp != NULL && temp->itemCode != i) {                // Search for the key to be deleted
        prev = temp;                                             //  keep track of the previous node as we need to change 'prev->next'
        temp = temp->next;
    }
    if (temp == NULL){                                          // If key was not present in linked list
        printf("\nThe item does not exist");
        return;
    } 
    prev->next = temp->next;                                    // Unlink the node from linked list
    free(temp);                                                 // Free memory
    printf("\nItem deleted successfully");
}

int main()
{
    int choice, new_itemCode, q, p;                 // Declare variables
    struct Node* head = NULL;                       // Start with the empty list
    char desc[500]; 
    while (1)
    {
        printf("\n\n******MAIN MENU******\n");      // Print menu options
        printf("1. Add Items\n");
        printf("2. Display Items\n");
        printf("3. Edit Itmes\n");
        printf("4. Delete Itmes\n");
        printf("5. EXIT\n");
        printf("Enter your option: ");              // Take choice input
        scanf("%d", &choice);
        
        switch (choice)                             // Switch case implemenation
        {
        case 1:
            printf("\nEnter the Item Code: ");
            scanf("%d",&new_itemCode);              // Take input of Item Code
            printf("Enter the Description: ");
            scanf("%s",&desc);                      // Take input of Description
            printf("Enter the Quantity: ");
            scanf("%d",&q);                         // Take input of Quantity
            printf("Enter the Price: ");
            scanf("%d",&p);                         // Take input of Price
            struct Node* n = node(new_itemCode,desc,q,p);
            insertNode(&head, n);
            printf("\nItem inserted successfully");
            break;

        case 2:
            printList(head);                                // Display the list of item
            break;

        case 3:
            printf("\nEnter the Item Code to edit: ");
            scanf("%d",&new_itemCode);
            struct Node* pos = find(head,new_itemCode);     // Check if item exists in list 
            if(pos){
                printf("Enter the Description: ");
                scanf("%s",&desc);                          // Take input of Description
                printf("Enter the Quantity: ");
                scanf("%d",&q);                             // Take input of Quantity
                printf("Enter the Price: ");
                scanf("%d",&p);                             // Take input of Price
                edit(pos,desc,q,p);                         // Call the edit function
                printf("\nThe list has been updated");
            }
            else{
                printf("\nThe item does not exist");        // Print if item does'nt exist
            }
            break;

        case 4:
            printf("\nEnter the Item Code to delete: ");
            scanf("%d",&new_itemCode);                      // Take input of Item code
            del(&head,new_itemCode);                        // Call del function
            break;

        case 5:
            exit(0);                                        // Exit program
            break;
        }
    }
    return 0;
}
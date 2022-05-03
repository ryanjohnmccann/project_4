
#ifndef PROJECT_4_LINKED_LIST_H
#define PROJECT_4_LINKED_LIST_H

// Linked list reference code: https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/

// A linked list node
struct Node {
    int data;
    struct Node *next;
};

/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct Node **head_ref, int new_data);

/* Given a node prev_node, insert a new node after the given
prev_node */
void insertAfter(struct Node *prev_node, int new_data);

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct Node **head_ref, int new_data);

/* Given a reference (pointer to pointer) to the head of a
   list and a key, deletes the first occurrence of key in
   linked list */
void deleteNode(struct Node **head_ref, int key);

// This function prints contents of linked list starting
// from the given node
void printList(struct Node *node);

#endif

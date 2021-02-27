#include <stdio.h>
#include <stdlib.h>

// Linked List setup
struct Node
{
    short testData;
	struct Node *next;
};
struct Node *head = NULL; // front of the linked-list

void ll_insertFront(short data);
void ll_insertAtIndex(short index, short data);
short ll_traverseToIndex(short index);
void ll_removeFromIndex(short index);
void ll_replaceIndex(short index, short data);
short ll_getLength();
void ll_merge();

int main() {
    ll_insertFront(16);
    ll_insertFront(12);
    ll_insertFront(10);

    for(short i=0;i<3;i++)
    {
        printf(ll_traverseToIndex(i));
    }
    return(0);
}


// Linked List functions

void ll_insertFront(short data) {
    struct Node *temp;
    temp = (struct Node *) malloc (sizeof(struct Node));
    if (temp == NULL) {
        printf("ERROR: Memory size-limit reached");
        exit(0);
    }

    temp->testData = data;
    if (head == NULL) // Initializing linked list
    {
        head = temp;
        temp->next = NULL;
    }
    else // insert element at front
    {
        temp->next = head; // point new element to the first element
        head = temp; // point head to new element
    }
}

void ll_insertAtIndex(short index, short data) {

}

short ll_traverseToIndex(short index) {
    struct Node *ptr;
    if (head == NULL)
        return NULL;
    else
    {
        ptr = head;
        for(short i=0; i<index; index++)
            ptr=ptr->next;
        return ptr->testData;
    }
}

void ll_removeFromIndex(short index) {

}

void ll_replaceIndex(short index, short data) {

}

short ll_getLength()
{
    short length;



    return length;
}

void ll_merge() {
    //idk if i even need this
}
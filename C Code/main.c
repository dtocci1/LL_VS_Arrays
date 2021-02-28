#include <stdio.h>
#include <stdlib.h>

// Linked List setup
struct Node
{
    short testData;
	struct Node *next;
};
struct Node *head = NULL; // front of the linked-list


void ll_insertFront(short data); // done
void ll_insertAtIndex(short index, short data); // done
short ll_traverseToIndex(short index); // done
void ll_removeFromIndex(short index); // done
void ll_replaceIndex(short index, short data); // done
short ll_getLength(); // done
void ll_merge();
void ll_printList(); // done

int main() {
    ll_insertFront(1);
    ll_insertFront(2);
    ll_insertFront(3);

    ll_printList();

    ll_replaceIndex(1,5);

    ll_printList();
    printf("%d",ll_getLength());

}


// Linked List functions

void ll_insertFront(short data) {
    struct Node *temp;
    temp = (struct Node *) malloc (sizeof(struct Node));
    if (temp == NULL) {
        printf("ERROR: Memory size-limit reached");
        exit(0);
    }

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
        temp->testData = data;
}

void ll_insertAtIndex(short index, short data) {
    struct Node *ptr = NULL;
    struct Node *oldPtr = NULL;
    struct Node *temp;

    if(head == NULL)
        return;

    ptr = head;
    for (short i=0;i<index-1;i++)
        ptr = ptr->next;

    oldPtr = ptr->next;
    temp = (struct Node *) malloc (sizeof(struct Node));

    if (temp == NULL) {
        printf("ERROR: Memory size-limit reached");
        exit(0);
    }

    ptr->next = temp;
    temp->next = oldPtr;
    temp->testData = data;
}

short ll_traverseToIndex(short index) {
    struct Node *ptr = NULL;
    if (head == NULL)
        return 0;

    ptr = head;
    for(short i=0; i<index; i++)
        ptr=ptr->next;
    return ptr->testData;
}

void ll_removeFromIndex(short index) {
    struct Node *ptr = NULL;
    struct Node *nextCell = NULL;

    if (head == NULL)
        return;
    
    // Traverse to cell before removal
    ptr = head;
    for(short i=0; i<index-1; i++)
        ptr = ptr->next;
    nextCell = ptr->next->next;
    free(ptr->next);
    ptr->next = nextCell;
}

void ll_replaceIndex(short index, short data) {
    struct Node *ptr = head;

    for(short i=0;i<index;i++)
        ptr=ptr->next;
    
    ptr->testData = data;
}

short ll_getLength()
{
    struct Node *ptr = head; 
    short length = 1;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        length++;
    }

    return length;
}

void ll_merge() {
    //idk if i even need this
}

void ll_printList() {
    struct Node *ptr;
    if (ptr == NULL)
        return;
    else
    {
        short count = 0;
        ptr = head;
        while (ptr != NULL) {
            printf("[%d]: %d\n", count, ptr->testData);
            ptr = ptr->next;
            count++;
        }
    }
}

// Linked List functions
#ifndef LINKEDLIST_H_   /* Include guard */
#define LINKEDLIST_H_
struct Node
{
    short testData;
	struct Node *next;
};

void ll_insertFront(struct Node** head, short data) {
    struct Node *temp;
    temp = (struct Node *) malloc (sizeof(struct Node));
    if (temp == NULL) {
        printf("ERROR: Memory size-limit reached");
        exit(0);
    }

    if (*head == NULL) // Initializing linked list
    {
        *head = temp;
        temp->next = NULL;
    }
    else // insert element at front
    {
        temp->next = *head; // point new element to the first element
        *head = temp; // point head to new element
    }
    temp->testData = data;
}

void ll_insertEnd(struct Node** head, short data) {
    struct Node *temp;
    struct Node *ptr = *head;

    temp = (struct Node *) malloc (sizeof(struct Node));
    if (temp == NULL) {
        printf("ERROR: Memory size-limit reached");
        exit(0);
    }
    if (*head == NULL) // Initializing linked list
    {
        *head = temp;
        temp->next = NULL;
    }
    else // Insert element at end
    {
        while(ptr->next != NULL)
            ptr = ptr->next;

        ptr->next = temp;
        temp->next = NULL;
    }
    temp->testData = data;
}

void ll_insertAtIndex(struct Node** head, short index, short data) {
    struct Node *ptr = NULL;
    struct Node *oldPtr = NULL;
    struct Node *temp;

    if(*head == NULL)
        return;

    ptr = *head;
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

short ll_traverseToIndex(struct Node** head, short index) {
    struct Node *ptr = NULL;
    if (*head == NULL)
        return 0;

    ptr = *head;
    for(short i=0; i<index; i++)
        ptr=ptr->next;
    return ptr->testData;
}

void ll_removeFromIndex(struct Node** head, short index) {
    struct Node *ptr = NULL;
    struct Node *nextCell = NULL;

    if (*head == NULL)
        return;
    
    // Traverse to cell before removal
    ptr = *head;
    for(short i=0; i<index-1; i++)
        ptr = ptr->next;
    nextCell = ptr->next->next;
    free(ptr->next);
    ptr->next = nextCell;
}

void ll_deleteList(struct Node** head) {
    struct Node *current;
    struct Node *next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

void ll_replaceIndex(struct Node** head, short index, short data) {
    struct Node *ptr = *head;

    for(short i=0;i<index;i++)
        ptr=ptr->next;
    
    ptr->testData = data;
}

short ll_getLength(struct Node** head)
{
    struct Node *ptr = *head; 
    short length = 1;

    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        length++;
    }

    return length;
}

void ll_merge(struct Node** head1, struct Node** head2) {
    struct Node *ptr = *head1;

    while(ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = *head2;
}

void ll_printList(struct Node** head) {
    struct Node *ptr;

    ptr = *head;
    if (ptr == NULL)
        return;
    else
    {
        short count = 0;
        ptr = *head;
        while (ptr != NULL) {
            printf("[%d]: %d\n", count, ptr->testData);
            ptr = ptr->next;
            count++;
        }
    }
}


#endif // LINKEDLIST_H_
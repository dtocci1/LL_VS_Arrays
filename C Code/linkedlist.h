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
    struct Node *prevPtr = NULL;
    struct Node *nextPtr = NULL;
    struct Node *temp;

    if(*head == NULL)
        return;
    prevPtr = *head;

    temp = (struct Node *) malloc (sizeof(struct Node));

    if (temp == NULL) {
        printf("ERROR: Memory size-limit reached");
        exit(0);
    }

    if (index == 0) {
        temp->next = *head; // point new element to the first element
        temp->testData = data;
        *head = temp; // point head to new element
        return;
    }

    for (short i=0;i<index-1;i++) 
        prevPtr = prevPtr->next;
    

    nextPtr = prevPtr->next;
    prevPtr->next = temp;
    temp->next = nextPtr;
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
    struct Node *temp = NULL;
    struct Node *prevCell = NULL;
    
    if (*head == NULL)
        return;

    temp = *head;
    if (index == 0) {
        *head = temp->next;
        free(temp);
        return;
    }
    // Traverse to cell before removal

    for(short i=0; i<index-1; i++) 
        temp = temp->next;
    
    prevCell = temp;
    prevCell->next = temp->next->next;
    temp = temp->next;
    free(temp);
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

// *** QUICK SORT FUNCTIONS ***
// Functions Pseudocode from GeeksforGeeks:
//  https://www.geeksforgeeks.org/quick-sort/
// Modified to work with linked lists

void ll_swap(struct Node** head, int index1, int index2) {
    short temp1, temp2;
    temp1 = ll_traverseToIndex(head, index1);
    temp2 = ll_traverseToIndex(head, index2);
    //printf("Swapping %d and %d", temp1, temp2);
    ll_replaceIndex(head, index1, temp2);
    ll_replaceIndex(head, index2, temp1);
}

int ll_quickSwap(struct Node** head, short start, short end) {
    int pivot = 0;
    int i = 0;

    pivot = ll_traverseToIndex(head, end);
    i = start-1;
    for(int j = start; j <= end - 1; j++){    
        // If current element is smaller
        // than the pivot
        if ((ll_traverseToIndex(head, j)) < pivot)
        {
             
            // Increment index of
            // smaller element
            i++;
            ll_swap(head, i, j);
        }
    }
    ll_swap(head, i+1, end);
    return (i+1);
}

void ll_quickSort(struct Node** head, short start, short end) {
    int pivot = 0;
    if (start < end) {
        pivot = ll_quickSwap(head, start, end);

        ll_quickSort(head, start, pivot-1);
        ll_quickSort(head, pivot+1, end);
    }
}

#endif // LINKEDLIST_H_
/* Linked List functions /
* ll_insertFront
* ll_insertEnd
* ll_insertAtIndex
* ll_traverseToIndex
* ll_removeFromIndex
* ll_deleteList
* ll_replaceIndex
* ll_getLength
* ll_merge
* ll_printList
* - QuickSort Functions -
* ll_swap
* ll_quickSwap
* ll_quickSort
*/

#ifndef LINKEDLIST_H_   /* Include guard */
#define LINKEDLIST_H_

struct Node
{
    short testData;
	struct Node *next;
};

// This function inserts a new element at the start of the linked list, as opposed to appending it to the end
// The head will point to this new element
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

// This function will append an element to the end of the linked list
// It needs to traverse the linked list first though, causing a much 
// slower insertion time
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

// This function will insert an element at any index provided. There is no bounds checking
// so only good numbers will let it run with the program. Again, the program needs to traverse
// to the insertion point
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

// This function will traverse to any index in the linked-list. Upon arrival
// it will return the data stored in the cell.
short ll_traverseToIndex(struct Node** head, short index) {
    struct Node *ptr = NULL;
    if (*head == NULL)
        return 0;

    ptr = *head;
    for(short i=0; i<index; i++)
        ptr=ptr->next;
    return ptr->testData;
}

// This function will remove any element from the linked list by providing
// it with an index. Since it is a dynamic data storage, the deleted cell will
// be freed from memory
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

// This function will traverse the entire linked list freeing every cell
// created. At the end, the head of the list will be pointed to NULL
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

// This function will replace the data of a cell in the linked-list
void ll_replaceIndex(struct Node** head, short index, short data) {
    struct Node *ptr = *head;

    for(short i=0;i<index;i++)
        ptr=ptr->next;
    
    ptr->testData = data;
}

// This function returns the total length of the linked-list. Currently it
// determine this by traversing it, but a math equation could be made to calculate
// the length to save time.
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

// This function will merge to linked lists. It does this by pointed the end of the first
// linked list to the start of the second linked list. This will leave the pointer to head2
// available to index the middle of the merged lists, assuming they are equal in length
void ll_merge(struct Node** head1, struct Node** head2) {
    struct Node *ptr = *head1;

    while(ptr->next != NULL)
        ptr = ptr->next;

    ptr->next = *head2;
}

// This function prints out all the elements in the linked-list along with their index
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
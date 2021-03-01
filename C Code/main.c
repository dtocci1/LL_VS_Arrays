#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h" // Header file with ll functions and Node setup

void a_insertAtIndex(short array1[], short len, short index, short data);

int main() {
    struct Node *head1 = NULL; // front of the linked-list 1
    struct Node *head2 = NULL; // front of the linked-list 1
    short test1[5] = {1,2,3,4};
    a_insertAtIndex(test1,5, 4, 5);
    //printf("%d", test1[4]);
}

// Array functions
/*
    * Insert element
    * Remove element
    * Merge
    * Print
*/

void a_insertAtIndex(short array1[], short len, short index, short data) {
    // Shifts elements in array to insert element, assumes there is room in the array
    for(short i = len-1; i>=index; i--)
        array1[i+1] = array1[i];
    array1[index] = data;
}
/*
void a_removeFromIndex() {

}

void a_merge() {

}

void a_print() {
    
}
*/
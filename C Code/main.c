#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h" // Header file with ll functions and Node setup

#define TEST_LENGTH 5 // array and linked-list length for test

void a_insertAtIndex(short array1[], short data, short index, short length);
void a_print(short array[], short length);
void a_removeFromIndex(short array[], short index, short length);

void main() {
    struct Node *head1 = NULL; // front of the linked-list 1
    struct Node *head2 = NULL; // front of the linked-list 1
    short test1[4] = {1,2,3,4};
    short test2[4] = {5,6,7,8};
    short merge[8] = {};
    
}

// Array functions
/*
    * Insert element XXXXXX
    * Remove element
    * Merge
    * Print XXXXX
*/

void a_insertAtIndex(short array[], short data, short index, short length) {
    // Shifts elements in array to insert element, assumes there is room in the array
    for(short i = length-2; i>=index; i--)
        array[i+1] = array[i];
    array[index] = data;
}

void a_removeFromIndex(short array[], short index, short length) {
    // Navigates to index specified then shifts everything to the left one, "deleting" the cell, leaving room at the end of the array
    for(short i = index; i<length; i++)
        array[i] = array[i+1];
    array[length-1] = 0; // 0 represents NULL content as you cannot "remove" from pre-allocated space, this will always be at the end of the array

}

void a_merge(short array1[], short length1, short array2[], short length2, short mergedArray[]) {
    for(short i = 0;)
}

void a_print(short array[], short length) {
    for (short i = 0; i<length; i++) {
        printf("%d: %d\n",i,array[i]);
    }
}
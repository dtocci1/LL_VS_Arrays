#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "linkedlist.h" // Header file with ll functions and Node setup
#include "array.h"      // Header file with array functions 

#define TEST_LENGTH 1024    // array and linked-list length for test
#define TEST_CYCLES 100000  // run operation this many times, average time
#define OPERATION 1         // operation to be tested, 1-insert, 2-remove, 3-traverse, 4-replace, 5-merge
#define SEED 5  //time(0)   // seed for random numbers, allows for repeatability

void tik();
void tok();
double elapsedTime();

clock_t runTime;

void main() {
    double executionTime, averageTime;
    int operation = OPERATION;

    struct Node* head1 = NULL; // front of the linked-list 1
    struct Node* head2 = NULL; // front of the linked-list 1

    short array1[TEST_LENGTH] = {};
    short array2[TEST_LENGTH] = {};

    srand(SEED); 

    // Populate arrays with random data
    for (short i = 0; i < TEST_LENGTH; i++)
        array1[i] = rand() % 32000; // generate 0 to 32000 - approximate max for short

    // Populate linked list data
    for (short i = 0; i < TEST_LENGTH; i++) 
        ll_insertFront(&head1,rand() % 32000);


    // Run test with specified operation
    switch (operation) {
    case 1: // insert

        break;
    case 2: // remove

        break;
    case 3: // traverse

        break;
    case 4: // replace

        break;
    case 5: // merge

        break;
    }
}

void tik() {
    runTime = clock();
}

void tok() {
    runTime = clock() - runTime;
}

double elapsedTime() {
    return ((double)runTime)/CLOCKS_PER_SEC;
}
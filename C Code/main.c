#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h" // Header file with ll functions and Node setup
#include "array.h"      // Header file with array functions 

#define TEST_LENGTH 5       // array and linked-list length for test
#define TEST_CYCLES 100000  // run operation this many times, average time
#define OPERATION "temp"    // operation to be tested
#define SEED 5              // seed for random numbers, allows for repeatability

void main() {
    time_t startTime, endTime;
    double executionTime, averageTime;

    struct Node* head1 = NULL; // front of the linked-list 1
    struct Node* head2 = NULL; // front of the linked-list 1

    short array1[TEST_LENGTH] = {};
    short array2[TEST_LENGTH] = {};

    srand(SEED);

    // Populate arrays with random data
    for (short i = 0; i < TEST_LENGTH; i++) {
        array1[i] = rand()

    }

    // Populate linked list data
    for (short i = 0; i < TEST_LENGTH; i++) {


    }

    // Run test with specified operation
    switch (OPERATION) {
    case "insert":

        break;
    case "remove":

        break;
    case "traverse":

        break;
    case "replace":

        break;
    case "merge":

        break;
    }
}
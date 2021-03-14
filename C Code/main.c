/*
 * Filename: LL_VS_Arrays/C Code/main.c
 * Path: LL_VS_Arrays/C Code
 * Created Date: Saturday, March 13th 2021, 2:17:39 pm
 * Author: Dylan Tocci
 * 
 * Copyright (c) 2021 UMass Dartmouth
 * 
 * Desc: add l8r
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h" // Header file with ll functions and Node setup
#include "array.h"      // Header file with array functions 

#define TEST_LENGTH 1024    // array and linked-list length for test
#define TEST_CYCLES 10000  // run operation this many times, average time
#define OPERATION 1         // operation to be tested, 1-populate, 2-insert, 3-remove, 
                            // 4-traverse, 5-replace, 6-merge
#define SEED time(0)        // seed for random numbers, gives option for repeatability

void tik();
void tok();
double elapsedTime();

clock_t runTime;

void main() {
    double executionTime, averageTime;
    int operation = OPERATION;
    double llAvgInsertFront = 0; double llAvgInsertEnd = 0; double aAvg = 0;

    struct Node* head1 = NULL; // front of the linked-list 1
    struct Node* head2 = NULL; // front of the linked-list 2
    short array1[TEST_LENGTH] = {};
    short array2[TEST_LENGTH] = {};

    srand(SEED); // Initialize randomizer seed (can be random or set based on SEED definition)


    // ***********************************************************************
    // ************************** POPULATE DATA ******************************
    // ***********************************************************************


    // Populate arrays with random data (only if this isn't being tested later)
    if (operation != 1) {
        for (short i = 0; i < TEST_LENGTH; i++)
            array1[i] = rand() % 32000;
        for (short i = 0; i < TEST_LENGTH; i++)
            array2[i] = rand() % 32000;

        // Populate linked list data - front insert
        for (short i = 0; i < TEST_LENGTH; i++) 
            ll_insertFront(&head1,rand() % 32000);

        // Populate linked list data - back insert
        for (short i = 0; i < TEST_LENGTH; i++) 
            ll_insertEnd(&head2, rand() % 32000);
    }
    // ***********************************************************************
    // ************************** RUN TESTS **********************************
    // ***********************************************************************


    // Run test with specified operation
    switch (operation) {
    // ************************** POPULATE *******************************
    case 1: 
        for(int i=0; i<TEST_CYCLES; i++) {
            tik();
            for (short i = 0; i < TEST_LENGTH; i++) 
                ll_insertFront(&head1,rand() % 32000);
            tok();
            llAvgInsertFront += elapsedTime();

            tik();
            for (short i = 0; i < TEST_LENGTH; i++) 
                ll_insertEnd(&head2, rand() % 32000);                
            tok();
            llAvgInsertEnd += elapsedTime();

            tik();
            for (short i = 0; i < TEST_LENGTH; i++)
                array1[i] = rand() % 32000;
            tok();
            aAvg += elapsedTime();

            // Purge lists and array
            ll_deleteList(&head1);
            ll_deleteList(&head2);
            for (short i = 0; i < TEST_LENGTH; i++)
                array1[i] = 0;

            // Display progress bar
            displayProgressBar(i);
        }

        llAvgInsertEnd = llAvgInsertEnd / TEST_CYCLES;
        llAvgInsertFront = llAvgInsertFront / TEST_CYCLES;
        aAvg = aAvg / TEST_CYCLES;
        printf("llIE %lf\n", llAvgInsertEnd);
        printf("llIF %lf\n", llAvgInsertFront);
        printf("aAVG %lf\n", aAvg);
        break;

    // ************************** INSERT *********************************
    case 2:
            
            // Insert at START

            // Insert at 1/8

            // Insert at 1/4

            // Insert at 1/2

            // Insert at 3/4

            // Insert at 7/8

            // Insert at END

        break;

    // ************************** REMOVE *********************************
    case 3: 
            
            // Remove at START

            // Remove at 1/8

            // Remove at 1/4

            // Remove at 1/2

            // Remove at 3/4

            // Remove at 7/8

            // Remove at END

        break;

    // ************************** TRAVERSE *******************************
    case 4:

        break;

    // ************************** REPLACE ********************************
    case 5:

        break;
    
    // ************************** MERGE **********************************
    case 6:

        break;
    }
}

void tik() {
    runTime=0;
    runTime = clock();
}

void tok() {
    runTime = clock() - runTime;
}

double elapsedTime() {
    return ((double)runTime)/CLOCKS_PER_SEC;
}

void displayProgressBar(int currentCycle) {
    float percentage, prevPercent = 0;
    
    percentage =  (double)currentCycle / TEST_CYCLES;
    prevPercent = (double)currentCycle / TEST_CYCLES-1; 

    if (round(percentage) != round(prevPercent)) { // only print % if it is a new %
        system("clear");
        printf("Percentage: %2.2f\n", percentage*100);
    }
}

float round(float var) 
{ 
    float value = (int)(var * 100 + .5); 
    return (float)value / 100; 
} 
  

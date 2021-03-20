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
 * TO DO:
 *      * Verify ll_insertAtIndex() is inserting efficiently
 *          currently insert at front and end take significantly longer, doesn't make sense
 *      * Complete code for other 4 operations
 *      * Allow option to pipe results to text file
 *      * POSSIBLY add in sorting test, not sure which
 */     

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h" // Header file with ll functions and Node setup
#include "array.h"      // Header file with array functions 

#define TEST_LENGTH 1024    // array and linked-list length for test
#define TEST_CYCLES 10000   // run operation this many times, average time
#define OPERATION 3         // operation to be tested, 1-populate, 2-insert, 3-remove, 
                            // 4-traverse, 5-replace, 6-merge
#define SEED time(0)        // seed for random numbers, gives option for repeatability

void tik();
void tok();
double elapsedTime();
void displayProgressBar(int);
void ll_runTest(struct Node** head, int operation, int testPoint, short *testData, double *timePassed);
void a_runTest(short array[], int operation, int testPoint, short *testData, double *timePassed);

clock_t runTime;

void main() {
    double executionTime, averageTime;
    int operation = OPERATION;
    double llAvgInsertFront, llAvgInsertEnd, aAvg = 0;
    double llStart, llOneEigth, llOneFourth, llOneHalf, llThreeFourth, llSevenEigth, llEnd = 0;
    double aStart, aOneEigth, aOneFourth, aOneHalf, aThreeFourth, aSevenEigth, aEnd = 0;
    short testData = 0; // used for insert/modify tests

    struct Node* head1 = NULL; // front of the linked-list 1
    struct Node* head2 = NULL; // front of the linked-list 2
    short array1[TEST_LENGTH] = {};
    short array2[TEST_LENGTH] = {};

    // ***********************************************************************
    // ************************** POPULATE DATA ******************************
    // ***********************************************************************

    srand(SEED); // Initialize randomizer seed (can be random or set based on SEED definition)

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

            // Display progress bar to user terminal
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
        for (int i=0; i<TEST_CYCLES; i++) {
            testData = rand() % 32000;
            
            ll_runTest(&head1, 2, 0, &testData, &llStart);
            a_runTest(array1, 2, 0, &testData, &aStart);
            
            ll_runTest(&head1, 2, 1/8*TEST_LENGTH, &testData, &llOneEigth);
            a_runTest(array1, 2, 1/8*TEST_LENGTH, &testData, &aOneEigth);

            ll_runTest(&head1, 2, 1/4*TEST_LENGTH, &testData, &llOneFourth);
            a_runTest(array1, 2, 1/4*TEST_LENGTH, &testData, &aOneFourth);

            ll_runTest(&head1, 2, 1/2*TEST_LENGTH, &testData, &llOneHalf);
            a_runTest(array1, 2, 1/2*TEST_LENGTH, &testData, &aOneHalf);

            ll_runTest(&head1, 2, 3/4*TEST_LENGTH, &testData, &llThreeFourth);
            a_runTest(array1, 2, 3/4*TEST_LENGTH, &testData, &aThreeFourth);

            ll_runTest(&head1, 2, 7/8*TEST_LENGTH, &testData, &llSevenEigth);
            a_runTest(array1, 2, 7/8*TEST_LENGTH, &testData, &aSevenEigth);

            ll_runTest(&head1, 2, TEST_LENGTH, &testData, &llEnd);
            a_runTest(array1, 2, TEST_LENGTH, &testData, &aEnd);

            // Remove inserted elements from linked-list
            for(int j=0; j<7; j++)
                ll_removeFromIndex(&head1,j); // removes first 7 elements inserted, allows for even comparison

            displayProgressBar(i);
        }
        
        // Average results
        llStart       = llStart       / TEST_LENGTH;
        aStart        = aStart        / TEST_LENGTH;
        llOneEigth    = llOneEigth    / TEST_LENGTH;
        aOneEigth     = aOneEigth     / TEST_LENGTH;
        llOneFourth   = llOneFourth   / TEST_LENGTH;
        aOneFourth    = aOneFourth    / TEST_LENGTH;
        llOneHalf     = llOneHalf     / TEST_LENGTH;
        aOneHalf      = aOneHalf      / TEST_LENGTH;
        llThreeFourth = llThreeFourth / TEST_LENGTH;
        aThreeFourth  = aThreeFourth  / TEST_LENGTH;
        llSevenEigth  = llSevenEigth  / TEST_LENGTH;
        aSevenEigth   = aSevenEigth   / TEST_LENGTH;
        llEnd         = llEnd         / TEST_LENGTH;
        aEnd          = aEnd          / TEST_LENGTH;

        // Display results (or pipe to text file maybe)
        printf("LL: %1.12lf A: %1.12lf\n",llStart,aStart);
        printf("LL: %1.12lf A: %1.12lf\n",llOneEigth,aOneEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneFourth,aOneFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneHalf,aOneHalf);
        printf("LL: %1.12lf A: %1.12lf\n",llThreeFourth,aThreeFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llSevenEigth,aSevenEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llEnd,aEnd);

        break;

    // ************************** REMOVE *********************************
    case 3: 
        for(int i = 0; i < TEST_CYCLES; i++) {
            
            ll_runTest(&head1, 3, 0, NULL, &llStart);
            a_runTest(array1, 3, 0, NULL, &aStart);
            ll_insertFront(&head1,rand() % 32000); 

            ll_runTest(&head1, 3, 1/8*TEST_LENGTH, NULL, &llOneEigth);
            a_runTest(array1, 3, 1/8*TEST_LENGTH, NULL, &aOneEigth);
            ll_insertFront(&head1,rand() % 32000); 

            ll_runTest(&head1, 3, 1/4*TEST_LENGTH, NULL, &llOneFourth);
            a_runTest(array1, 3, 1/4*TEST_LENGTH, NULL, &aOneFourth);
            ll_insertFront(&head1,rand() % 32000); 

            ll_runTest(&head1, 3, 1/2*TEST_LENGTH, NULL, &llOneHalf);
            a_runTest(array1, 3, 1/2*TEST_LENGTH, NULL, &aOneHalf);
            ll_insertFront(&head1,rand() % 32000); 

            ll_runTest(&head1, 3, 3/4*TEST_LENGTH, NULL, &llThreeFourth);
            a_runTest(array1, 3, 3/4*TEST_LENGTH, NULL, &aThreeFourth);
            ll_insertFront(&head1,rand() % 32000); 

            ll_runTest(&head1, 3, 7/8*TEST_LENGTH, NULL, &llSevenEigth);
            a_runTest(array1, 3, 7/8*TEST_LENGTH, NULL, &aSevenEigth);
            ll_insertFront(&head1,rand() % 32000); 

            ll_runTest(&head1, 3, TEST_LENGTH-1, NULL, &llEnd);
            a_runTest(array1, 3, TEST_LENGTH, NULL, &aEnd);
            ll_insertFront(&head1,rand() % 32000); 

            displayProgressBar(i);
        }

        // Average results
        llStart       = llStart       / TEST_LENGTH;
        aStart        = aStart        / TEST_LENGTH;
        llOneEigth    = llOneEigth    / TEST_LENGTH;
        aOneEigth     = aOneEigth     / TEST_LENGTH;
        llOneFourth   = llOneFourth   / TEST_LENGTH;
        aOneFourth    = aOneFourth    / TEST_LENGTH;
        llOneHalf     = llOneHalf     / TEST_LENGTH;
        aOneHalf      = aOneHalf      / TEST_LENGTH;
        llThreeFourth = llThreeFourth / TEST_LENGTH;
        aThreeFourth  = aThreeFourth  / TEST_LENGTH;
        llSevenEigth  = llSevenEigth  / TEST_LENGTH;
        aSevenEigth   = aSevenEigth   / TEST_LENGTH;
        llEnd         = llEnd         / TEST_LENGTH;
        aEnd          = aEnd          / TEST_LENGTH;

        // Display results (or pipe to text file maybe)
        printf("LL: %1.12lf A: %1.12lf\n",llStart,aStart);
        printf("LL: %1.12lf A: %1.12lf\n",llOneEigth,aOneEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneFourth,aOneFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneHalf,aOneHalf);
        printf("LL: %1.12lf A: %1.12lf\n",llThreeFourth,aThreeFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llSevenEigth,aSevenEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llEnd,aEnd);

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
  
void ll_runTest(struct Node** head, int operation, int testPoint, short *testData, double *timePassed) {
    switch(operation) {
    case 2:
        tik();
        ll_insertAtIndex(head,testPoint,*testData);
        tok();
        *timePassed += elapsedTime();
        break;
    case 3:
        tik();
        ll_removeFromIndex(head, testPoint);
        tok();
        *timePassed += elapsedTime();
        break;
    case 4:
        
        break;
    case 5:
        
        break;
    case 6:
        
        break;
    default:
        break;
    }
    
}

void a_runTest(short array[], int operation, int testPoint, short *testData, double *timePassed) { // add pointer so we can pass NULL without C yelling at us
    switch(operation) {
    case 2:
        tik();
        a_insertAtIndex(array, *testData, testPoint, TEST_LENGTH);
        tok();
        *timePassed += elapsedTime();
        break;
    case 3:
        tik();
        a_removeFromIndex(array,testPoint,TEST_LENGTH);
        tok();
        *timePassed += elapsedTime();
        break;
    case 4:
        
        break;
    case 5:
        
        break;
    case 6:
        
        break;
    default:
        break;
    }   
}
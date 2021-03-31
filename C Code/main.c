/*
 * Filename: LL_VS_Arrays/C Code/main.c
 * Path: LL_VS_Arrays/C Code
 * Created Date: Saturday, March 13th 2021, 2:17:39 pm
 * Author: Dylan Tocci
 * 
 * Copyright (c) 2021 UMass Dartmouth
 * 
 * Desc: 
 *  This program directly benchmarks arrays and linked-lists with seven different operations. These are:
 *      1. Population
 *      2. Element Insertions
 *      3. Element Removal
 *      4. Traversal
 *      5. Element Replacement
 *      6. Merging
 *      7. Quicksort
 * 
 * Operations can be changed by changing the value of the OPERATION definition. Additionally, one can change the size of the data using the TEST_LENGTH definition
 * and the number of times tests are run by using the TEST_CYCLES definition. Lastly, if one requries consistant results, one can change the seed for random
 * number generation via use of the SEED definition. By default it is set to time(0) to randomize the data, but this can be set to a constant. Currently, the program will
 * crash on Windows or as the program makes use of the system function, with it running linux commands. This can be fixed in a later iteration if necessary.
 * 
 * TO DO:
 *      * Clean up code
 *      * Add comments to header file functions
 *      * Run tests and graph results
 *      * Add windows/mac support for displayProgress function
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedlist.h" // Header file with ll functions and Node setup
#include "array.h"      // Header file with array functions 

#define TEST_LENGTH 8      // array and linked-list length for test
#define TEST_CYCLES 10000   // run operation this many times, average time
#define OPERATION 2         // operation to be tested, 1-populate, 2-insert, 3-remove, 
                            // 4-traverse, 5-replace, 6-merge, 7 quicksort
#define SEED time(0)        // seed for random numbers, gives option for repeatability

void tik();
void tok();
double elapsedTime();
void displayProgressBar(int);
void ll_runTest(struct Node** head, int operation, int testPoint, short *testData, double *timePassed);
void a_runTest(short array[], int operation, int testPoint, short *testData, double *timePassed);
float shortRound(float var);

clock_t runTime;

void main() {
    double executionTime = 0, averageTime = 0;
    int operation = OPERATION;
    double llAvgInsertFront = 0, llAvgInsertEnd = 0, aAvg = 0;
    double llStart = 0, llOneEigth = 0, llOneFourth = 0, llOneHalf = 0, llThreeFourth = 0, llSevenEigth = 0, llEnd = 0;
    double aStart = 0, aOneEigth = 0, aOneFourth = 0, aOneHalf = 0, aThreeFourth = 0, aSevenEigth = 0, aEnd = 0;
    short testData = 0; // used for insert/modify test
    struct Node* head1 = NULL; // front of the linked-list 1
    struct Node* head2 = NULL; // front of the linked-list 2
    short array1[TEST_LENGTH] = {};
    short array2[TEST_LENGTH] = {};
    short mergedArray[TEST_LENGTH * 2] = {};
    short testPoints[7] = {0,(double)1/8*TEST_LENGTH, (double)1/4*TEST_LENGTH, (double)1/2*TEST_LENGTH, (double)3/4*TEST_LENGTH, (double)7/8*TEST_LENGTH, TEST_LENGTH-1};


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
        printf("llIE %1.12lf\n", llAvgInsertEnd);
        printf("llIF %1.12lf\n", llAvgInsertFront);
        printf("aAVG %1.12lf\n", aAvg);
        break;

    // ************************** INSERT *********************************
    case 2:
        for (int i=0; i<TEST_CYCLES; i++) {
            testData = rand() % 32000;
            
            ll_runTest(&head1, 2, testPoints[0], &testData, &llStart);
            a_runTest(array1, 2, testPoints[0], &testData, &aStart);
            
            ll_runTest(&head1, 2, testPoints[1], &testData, &llOneEigth);
            a_runTest(array1, 2, testPoints[1], &testData, &aOneEigth);

            ll_runTest(&head1, 2, testPoints[2], &testData, &llOneFourth);
            a_runTest(array1, 2, testPoints[2], &testData, &aOneFourth);

            ll_runTest(&head1, 2, testPoints[3], &testData, &llOneHalf);
            a_runTest(array1, 2, testPoints[3], &testData, &aOneHalf);

            ll_runTest(&head1, 2, testPoints[4], &testData, &llThreeFourth);
            a_runTest(array1, 2, testPoints[4], &testData, &aThreeFourth);

            ll_runTest(&head1, 2, testPoints[5], &testData, &llSevenEigth);
            a_runTest(array1, 2, testPoints[5], &testData, &aSevenEigth);

            ll_runTest(&head1, 2, testPoints[6], &testData, &llEnd);
            a_runTest(array1, 2, testPoints[6], &testData, &aEnd);

            displayProgressBar(i);
        }
        
        // Average results
        llStart       = llStart       / TEST_CYCLES;
        aStart        = aStart        / TEST_CYCLES;
        llOneEigth    = llOneEigth    / TEST_CYCLES;
        aOneEigth     = aOneEigth     / TEST_CYCLES;
        llOneFourth   = llOneFourth   / TEST_CYCLES;
        aOneFourth    = aOneFourth    / TEST_CYCLES;
        llOneHalf     = llOneHalf     / TEST_CYCLES;
        aOneHalf      = aOneHalf      / TEST_CYCLES;
        llThreeFourth = llThreeFourth / TEST_CYCLES;
        aThreeFourth  = aThreeFourth  / TEST_CYCLES;
        llSevenEigth  = llSevenEigth  / TEST_CYCLES;
        aSevenEigth   = aSevenEigth   / TEST_CYCLES;
        llEnd         = llEnd         / TEST_CYCLES;
        aEnd          = aEnd          / TEST_CYCLES;

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
            ll_runTest(&head1, 3, testPoints[0], NULL, &llStart);
            a_runTest(array1, 3, testPoints[0], NULL, &aStart);

            ll_runTest(&head1, 3, testPoints[1], NULL, &llOneEigth);
            a_runTest(array1, 3, testPoints[1], NULL, &aOneEigth);

            ll_runTest(&head1, 3, testPoints[2], NULL, &llOneFourth);
            a_runTest(array1, 3, testPoints[2], NULL, &aOneFourth);

            ll_runTest(&head1, 3, testPoints[3], NULL, &llOneHalf);
            a_runTest(array1, 3, testPoints[3], NULL, &aOneHalf);

            ll_runTest(&head1, 3, testPoints[4], NULL, &llThreeFourth);
            a_runTest(array1, 3, testPoints[4], NULL, &aThreeFourth);

            ll_runTest(&head1, 3, testPoints[5], NULL, &llSevenEigth);
            a_runTest(array1, 3, testPoints[5], NULL, &aSevenEigth);

            ll_runTest(&head1, 3, testPoints[6], NULL, &llEnd);
            a_runTest(array1, 3, testPoints[6], NULL, &aEnd);

            displayProgressBar(i);
        }

        // Average results
        llStart       = llStart       / TEST_CYCLES;
        aStart        = aStart        / TEST_CYCLES;
        llOneEigth    = llOneEigth    / TEST_CYCLES;
        aOneEigth     = aOneEigth     / TEST_CYCLES;
        llOneFourth   = llOneFourth   / TEST_CYCLES;
        aOneFourth    = aOneFourth    / TEST_CYCLES;
        llOneHalf     = llOneHalf     / TEST_CYCLES;
        aOneHalf      = aOneHalf      / TEST_CYCLES;
        llThreeFourth = llThreeFourth / TEST_CYCLES;
        aThreeFourth  = aThreeFourth  / TEST_CYCLES;
        llSevenEigth  = llSevenEigth  / TEST_CYCLES;
        aSevenEigth   = aSevenEigth   / TEST_CYCLES;
        llEnd         = llEnd         / TEST_CYCLES;
        aEnd          = aEnd          / TEST_CYCLES;
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
        for(int i=0; i < TEST_CYCLES; i++) {
            ll_runTest(&head1, 4, testPoints[0], NULL, &llStart);
            a_runTest(array1, 4, testPoints[0], NULL, &aStart);

            ll_runTest(&head1, 4, testPoints[1], NULL, &llOneEigth);
            a_runTest(array1, 4, testPoints[1], NULL, &aOneEigth);

            ll_runTest(&head1, 4, testPoints[2], NULL, &llOneFourth);
            a_runTest(array1, 4, testPoints[2], NULL, &aOneFourth);

            ll_runTest(&head1, 4, testPoints[3], NULL, &llOneHalf);
            a_runTest(array1, 4, testPoints[3], NULL, &aOneHalf);

            ll_runTest(&head1, 4, testPoints[4], NULL, &llThreeFourth);
            a_runTest(array1, 4, testPoints[4], NULL, &aThreeFourth);

            ll_runTest(&head1, 4, testPoints[5], NULL, &llSevenEigth);
            a_runTest(array1, 4, testPoints[5], NULL, &aSevenEigth);

            ll_runTest(&head1, 4, testPoints[6], NULL, &llEnd);
            a_runTest(array1, 4, testPoints[6], NULL, &aEnd);

            displayProgressBar(i);
        }

        // Average results
        llStart       = llStart       / TEST_CYCLES;
        aStart        = aStart        / TEST_CYCLES;
        llOneEigth    = llOneEigth    / TEST_CYCLES;
        aOneEigth     = aOneEigth     / TEST_CYCLES;
        llOneFourth   = llOneFourth   / TEST_CYCLES;
        aOneFourth    = aOneFourth    / TEST_CYCLES;
        llOneHalf     = llOneHalf     / TEST_CYCLES;
        aOneHalf      = aOneHalf      / TEST_CYCLES;
        llThreeFourth = llThreeFourth / TEST_CYCLES;
        aThreeFourth  = aThreeFourth  / TEST_CYCLES;
        llSevenEigth  = llSevenEigth  / TEST_CYCLES;
        aSevenEigth   = aSevenEigth   / TEST_CYCLES;
        llEnd         = llEnd         / TEST_CYCLES;
        aEnd          = aEnd          / TEST_CYCLES;

        // Display results (or pipe to text file maybe)
        printf("LL: %1.12lf A: %1.12lf\n",llStart,aStart);
        printf("LL: %1.12lf A: %1.12lf\n",llOneEigth,aOneEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneFourth,aOneFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneHalf,aOneHalf);
        printf("LL: %1.12lf A: %1.12lf\n",llThreeFourth,aThreeFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llSevenEigth,aSevenEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llEnd,aEnd);

        break;

    // ************************** REPLACE ********************************
    case 5:
        for(int i=0; i < TEST_CYCLES; i++) {
            testData = rand() % 32000;

            ll_runTest(&head1, 5, testPoints[0], &testData, &llStart);
            a_runTest(array1, 5, testPoints[0], &testData, &aStart);

            ll_runTest(&head1, 5, testPoints[1], &testData, &llOneEigth);
            a_runTest(array1, 5, testPoints[1], &testData, &aOneEigth);

            ll_runTest(&head1, 5, testPoints[2], &testData, &llOneFourth);
            a_runTest(array1, 5, testPoints[2], &testData, &aOneFourth);

            ll_runTest(&head1, 5, testPoints[3], &testData, &llOneHalf);
            a_runTest(array1, 5, testPoints[3], &testData, &aOneHalf);

            ll_runTest(&head1, 5, testPoints[4], &testData, &llThreeFourth);
            a_runTest(array1, 5, testPoints[4], &testData, &aThreeFourth);

            ll_runTest(&head1, 5, testPoints[5], &testData, &llSevenEigth);
            a_runTest(array1, 5, testPoints[5], &testData, &aSevenEigth);

            ll_runTest(&head1, 5, testPoints[6], &testData, &llEnd);
            a_runTest(array1, 5, testPoints[6], &testData, &aEnd);

            displayProgressBar(i);
        }

        // Average results
        llStart       = llStart       / TEST_CYCLES;
        aStart        = aStart        / TEST_CYCLES;
        llOneEigth    = llOneEigth    / TEST_CYCLES;
        aOneEigth     = aOneEigth     / TEST_CYCLES;
        llOneFourth   = llOneFourth   / TEST_CYCLES;
        aOneFourth    = aOneFourth    / TEST_CYCLES;
        llOneHalf     = llOneHalf     / TEST_CYCLES;
        aOneHalf      = aOneHalf      / TEST_CYCLES;
        llThreeFourth = llThreeFourth / TEST_CYCLES;
        aThreeFourth  = aThreeFourth  / TEST_CYCLES;
        llSevenEigth  = llSevenEigth  / TEST_CYCLES;
        aSevenEigth   = aSevenEigth   / TEST_CYCLES;
        llEnd         = llEnd         / TEST_CYCLES;
        aEnd          = aEnd          / TEST_CYCLES;

        // Display results (or pipe to text file maybe)
        printf("LL: %1.12lf A: %1.12lf\n",llStart,aStart);
        printf("LL: %1.12lf A: %1.12lf\n",llOneEigth,aOneEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneFourth,aOneFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llOneHalf,aOneHalf);
        printf("LL: %1.12lf A: %1.12lf\n",llThreeFourth,aThreeFourth);
        printf("LL: %1.12lf A: %1.12lf\n",llSevenEigth,aSevenEigth);
        printf("LL: %1.12lf A: %1.12lf\n",llEnd,aEnd);

        break;
    
    // ************************** MERGE **********************************
    case 6:
        for(int i = 0; i < TEST_CYCLES; i++) {
            tik();
            ll_merge(&head1,&head2);
            tok();
            llStart += elapsedTime();

            tik();
            a_merge(array1,TEST_LENGTH,array2,TEST_LENGTH,mergedArray);
            tok();
            aStart += elapsedTime();

            //Rewrite linked list and arrays with new data
            ll_deleteList(&head1);
            ll_deleteList(&head2);
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

            displayProgressBar(i);
        }

        llStart       = llStart       / TEST_CYCLES;
        aStart        = aStart        / TEST_CYCLES;
        printf("LL: %1.12lf A: %1.12lf\n",llStart,aStart);

        break;
    
    // ************************** QUICK SORT **********************************
    case 7:
        for(int i = 0; i < TEST_CYCLES; i++) {
            tik();
            ll_quickSort(&head1, 0, TEST_LENGTH-1);
            tok();
            llStart += elapsedTime();

            tik();
            a_quickSort(array1, 0, TEST_LENGTH-1);
            tok();
            aStart += elapsedTime();

            //Rewrite linked list and arrays with new data
            ll_deleteList(&head1);
            ll_deleteList(&head2);
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

            displayProgressBar(i);
        }

        llStart       = llStart       / TEST_CYCLES;
        aStart        = aStart        / TEST_CYCLES;
        printf("LL: %1.12lf A: %1.12lf\n",llStart,aStart);

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

    if (shortRound(percentage) != shortRound(prevPercent)) { // only print % if it is a new %
        system("clear");
        printf("Percentage: %2.2f\n", percentage*100);
    }
}

float shortRound(float var) 
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
        ll_removeFromIndex(head,testPoint); // remove inserted point
        break;
    case 3:
        tik();
        ll_removeFromIndex(head, testPoint);
        tok();
        *timePassed += elapsedTime();
        ll_insertFront(head,rand()%32000); // reinsert data to removed point 
        break;
    case 4:
        tik();
        ll_traverseToIndex(head,testPoint);
        tok();
        *timePassed += elapsedTime();    
        break;
    case 5:
        tik();
        ll_replaceIndex(head, testPoint, *testData);
        tok();
        *timePassed += elapsedTime();
        break;
    default:
        printf("ERROR: Invalid operation");
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
        tik();
        array[testPoint];
        tok();
        *timePassed += elapsedTime();
        break;
    case 5:
        tik();
        array[testPoint] = *testData;
        tok();
        *timePassed += elapsedTime();
        break;
    default:
        printf("ERROR: Invalid operation");
        break;
    }   
}
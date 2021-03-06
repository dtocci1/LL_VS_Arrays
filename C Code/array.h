/* Array functions /
* a_insertAtIndex
* a_removeFromIndex
* a_merge
* a_print
* - QuickSort Functions -
* a_swap
* a_quickSwap
* a_quickSort
*/
#ifndef ARRAY_H_   /* Include guard */
#define ARRAY_H_

// Insert an element at the specified index in the array
void a_insertAtIndex(short array[], short data, short index, short length) {
    // Shifts elements in array to insert element, assumes there is room in the array
    for(short i = length-1; i>=index; i--)
        array[i+1] = array[i];
    array[index] = data;
}

// Removes an element from a specified index in the array
void a_removeFromIndex(short array[], short index, short length) {
    // Navigates to index specified then shifts everything to the left one, "deleting" the cell, leaving room at the end of the array
    for(short i = index; i<length; i++)
        array[i] = array[i+1];
    array[length-1] = 0; // 0 represents NULL content as you cannot "remove" from pre-allocated space, this will always be at the end of the array

}

// Merges to arrays together and saves it in a third array passed to the function (lengths must be equivalent)
void a_merge(short array1[], short length1, short array2[], short length2, short mergedArray[]) {
    for(short i = 0; i<(length1+length2); i++) {
        if(i < length1)
            mergedArray[i] = array1[i]; // Add in all of array1 first
        else
            mergedArray[i] = array2[i-length1]; // Add in all of array2 afterwords 
    }
}

// Prints out the contents of the cells in the array and their corresponding index
void a_print(short array[], short length) {
    for (short i = 0; i<length; i++) 
        printf("%d: %d\n",i,array[i]);
}

// *** QUICK SORT FUNCTIONS ***
// Functions Pseudocode from GeeksforGeeks:
//  https://www.geeksforgeeks.org/quick-sort/
// Modified to work with linked lists

void a_swap(short array[], int index1, int index2) {
    short temp;
    temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

int a_quickSwap(short array[], short start, short end) {
    int pivot = 0;
    int i = 0;

    pivot = array[end];
    i = start-1;
    for(int j = start; j <= end - 1; j++){    
        // If current element is smaller
        // than the pivot
        if (array[j] < pivot)
        {
             
            // Increment index of
            // smaller element
            i++;
            a_swap(array, i, j);
        }
    }
    a_swap(array, i+1, end);
    return (i+1);
}

void a_quickSort(short array[], short start, short end) {
    int pivot = 0;
    if (start < end) {
        pivot = a_quickSwap(array, start, end);

        a_quickSort(array, start, pivot-1);
        a_quickSort(array, pivot+1, end);
    }
}

#endif // ARRAY_H_
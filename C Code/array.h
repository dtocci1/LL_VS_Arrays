// Array functions
#ifndef ARRAY_H_   /* Include guard */
#define ARRAY_H_
void a_insertAtIndex(short array[], short data, short index, short length) {
    // Shifts elements in array to insert element, assumes there is room in the array
    for(short i = length-1; i>=index; i--)
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
    for(short i = 0; i<(length1+length2); i++) {
        if(i < length1)
            mergedArray[i] = array1[i]; // Add in all of array1 first
        else
            mergedArray[i] = array2[i-length1]; // Add in all of array2 afterwords 
    }
}

void a_print(short array[], short length) {
    for (short i = 0; i<length; i++) 
        printf("%d: %d\n",i,array[i]);
}
#endif // ARRAY_H_
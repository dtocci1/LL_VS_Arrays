# LL_VS_Arrays
This program directly benchmarks arrays and linked-lists with seven different operations. These are:
    1. Population
    2. Element Insertions
    3. Element Removal
    4. Traversal
    5. Element Replacement
    6. Merging
    7. Quicksort
  
Operations can be changed by changing the value of the OPERATION definition. Additionally, one can change the size of the data using the TEST_LENGTH definition and the number of times tests are run by using the TEST_CYCLES definition. Lastly, if one requries consistant results, one can change the seed for random number generation via use of the SEED definition. By default it is set to time(0) to randomize the data, but this can be set to a constant. Currently, the program will crash on Windows or as the program makes use of the system function, with it running linux commands. This can be fixed in a later iteration if necessary.
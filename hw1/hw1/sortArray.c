#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

int main(int argc, char* argv[argc+1])
{
    /* create pointer to file */
    FILE* in_file = fopen(argv[1], "r");

    /* grab array length to use in for loops */
    int length;
    fscanf(in_file, "%d", &length);

    /* pre-allocate even & odd arrays (max size is 20) */
    int evenArray[20];
    int oddArray[20];

    /* scan remaining elements in file to array */
    int current; 
    int evenCount = 0;
    int oddCount = 0;
    while(fscanf(in_file, "%d", &current) != EOF)
    {
        if (current % 2 == 0)
        {
            evenArray[evenCount] = current;
            evenCount++;
        } 
        else 
        {
            oddArray[oddCount] = current;
            oddCount++;
        }
    }
    fclose(in_file);
    /* insertion sort for even numbers (ascending) */
    for (int i = 1; i < evenCount; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (evenArray[j-1] > evenArray[j])
            {
                swap(&evenArray[j-1], &evenArray[j]);
            }
        }
    }
 
    /* insertion sort for odd numbers (descending) */
    for (int i = 1; i < oddCount; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (oddArray[j-1] < oddArray[j])
            {
                swap(&oddArray[j-1], &oddArray[j]);
            }
        }
    }
 
    /* print the sorted even array */
    for (int i = 0; i < evenCount; i++)
    {
        printf("%d\t", evenArray[i]);
    }
    /* print the sorted odd array */
    for (int i = 0; i < oddCount; i++)
    {
        printf("%d\t", oddArray[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}

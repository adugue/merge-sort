// Merge sort algorithm v3
// v2 -> improved to use varying amounts of numbers to sort using malloc (dynamic memory allocation)
// v3 -> modified to generate a specified amount of random numbers between 0 and 100 and then 
//       sort them
#include <stdio.h>
#include <stdlib.h>     /* atoi */
#include <time.h>

void sort(int size_unsorted, int unsorted[], int sorted[], int start);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error: no numbers were provided.\n");
        printf("Example of correct usage: ./merge_sort 42\n");
        return 1;
    }
    
    int size = atoi(argv[1]); 
    int N = 101;

    // allocate memory using malloc for array
    int *array = malloc(size * sizeof(int));
    if (array == NULL)
    {
        printf("Could not allocate memory to sort numbers(1).\n");
        return 1;
    }
    
    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL)
    {
        printf("Could not allocate memory to sort numbers(2).\n");
        return 1;
    }

    srandom(time(NULL));  // seeding random with the time
    for (int i = 0; i < size; i++)
    {
        // array[i] = (random() / ((double) RAND_MAX + 1)) * N;
        array[i] = random() % N;
        sorted[i] = 0;
    }    
    
    // Print array numbers
    printf("Numbers - unsorted: ");
    for (int i = 0; i < size; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
    
    // Sort using merge sort function
    sort(size, array, sorted, 0);

    // Result
    printf("Numbers - sorted:   ");
    for (int i = 0; i < size; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");

    // Free allocated memory
    free(array);
    free(sorted);
}

void sort(int size_unsorted, int unsorted[], int sorted[], int start)
{
    // Base case - only one number
    if (size_unsorted == 1) // Only one number
    {
        return;
    }

    // Sort left half of the array
    sort(size_unsorted/2, unsorted, sorted, start);

    // Sort right half of the array
    sort(size_unsorted - (size_unsorted/2), unsorted, sorted, start + size_unsorted/2);

    // Merge the two together
    int position = start;
    int pointer_left = start;
    int pointer_right = start + size_unsorted/2;

    for (position = start; position < start + size_unsorted; position++) 
    {
        if (pointer_left == (start + size_unsorted/2))  // if pointer_left has reached the end
        {
            sorted[position] = unsorted[pointer_right];
            pointer_right++;
        }
        else if (pointer_right == (start + size_unsorted))           // if pointer_right has reached the end
        {
            sorted[position] = unsorted[pointer_left];
            pointer_left++;       
        }
        else if (unsorted[pointer_left] < unsorted[pointer_right])      // pointer_left points to smaller element
        {
            sorted[position] = unsorted[pointer_left];
            pointer_left++;            
        }
        else // pointer_right points to smaller element
        {
            sorted[position] = unsorted[pointer_right];
            pointer_right++;
        }
    }

    for (position = start; position < start + size_unsorted; position++)
    {
        unsorted[position] = sorted[position];
    }

}

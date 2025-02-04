#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 10; // size of the array
    int* arr = (int*)malloc(n * sizeof(int));
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1; // initialize the array with values from 1 to n
    }

    #pragma omp parallel reduction(+:sum)
    {
        int local_sum = 0;
        for (int i = 0; i < n; i++) {
            local_sum += arr[i]; // compute the sum of the array elements in parallel
        }
        #pragma omp critical
        {
            sum += local_sum; // add the local sum to the global sum
        }
    }

    printf("The prefix sum of the array elements is %d\n", sum);

    free(arr);

    return 0;
}
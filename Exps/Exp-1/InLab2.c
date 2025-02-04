#include <stdio.h>
#include <omp.h>

void demonstrate_single() {
    #pragma omp parallel
    {
        printf("Thread %d: Before single directive\n", omp_get_thread_num());

        #pragma omp single
        {
            printf("Thread %d: Executing single block\n", omp_get_thread_num());
        }

        printf("Thread %d: After single directive\n", omp_get_thread_num());
    }
}

void demonstrate_barrier() {
    #pragma omp parallel
    {
        printf("Thread %d: Before barrier\n", omp_get_thread_num());

        #pragma omp barrier

        printf("Thread %d: After barrier\n", omp_get_thread_num());
    }
}

void demonstrate_atomic() {
    int sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        #pragma omp atomic
        sum += i;
    }

    printf("Final sum: %d\n", sum);
}

int main() {
    int choice;

    printf("Select a directive to demonstrate:\n");
    printf("1. Single Directive\n");
    printf("2. Barrier Directive\n");
    printf("3. Atomic Directive\n");
    printf("Enter your choice (1/2/3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nDemonstrating SINGLE Directive:\n");
            demonstrate_single();
            break;
        case 2:
            printf("\nDemonstrating BARRIER Directive:\n");
            demonstrate_barrier();
            break;
        case 3:
            printf("\nDemonstrating ATOMIC Directive:\n");
            demonstrate_atomic();
            break;
        default:
            printf("Invalid choice. Please select 1, 2, or 3.\n");
            break;
    }

    return 0;
}

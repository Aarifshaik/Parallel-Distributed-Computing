#include <stdio.h>
#include <omp.h>

void demonstrate_parallel_for() {
    int i;
    #pragma omp parallel for
    for (i = 0; i < 10; i++) {
        printf("Thread %d executes iteration %d\n", omp_get_thread_num(), i);
    }
}

void demonstrate_private_clause() {
    int x;
    #pragma omp parallel private(x)
    {
        x = omp_get_thread_num();
        printf("Thread %d has x = %d\n", omp_get_thread_num(), x);
    }
}

void demonstrate_shared_clause() {
    int x = 0;
    #pragma omp parallel shared(x)
    {
        #pragma omp critical
        {
            x += omp_get_thread_num();
            printf("Thread %d updates x to %d\n", omp_get_thread_num(), x);
        }
    }
    printf("Final value of x: %d\n", x);
}

void demonstrate_critical_directive() {
    int counter = 0;
    #pragma omp parallel
    {
        for (int i = 0; i < 5; i++) {
            #pragma omp critical
            {
                counter++;
                printf("Thread %d increments counter to %d\n", omp_get_thread_num(), counter);
            }
        }
    }
    printf("Final counter value: %d\n", counter);
}

void demonstrate_master_directive() {
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Master thread (thread 0) is executing this code.\n");
        }
    }
}

int global_var;
#pragma omp threadprivate(global_var)

void demonstrate_threadprivate_clause() {
    // int global_var;
    // #pragma omp threadprivate(global_var)

    global_var = 42;
    #pragma omp parallel
    {
        printf("Thread %d has global_var = %d\n", omp_get_thread_num(), global_var);
        global_var = omp_get_thread_num();
    }

    #pragma omp parallel
    {
        printf("Thread %d retains global_var = %d\n", omp_get_thread_num(), global_var);
    }
}

void demonstrate_default_clause() {
    int x = 10, y = 20;
    #pragma omp parallel default(none) shared(x) private(y)
    {
        y = omp_get_thread_num();
        printf("Thread %d: x = %d, y = %d\n", omp_get_thread_num(), x, y);
    }
}

void demonstrate_firstprivate_clause() {
    int x = 10;
    #pragma omp parallel firstprivate(x)
    {
        x += omp_get_thread_num();
        printf("Thread %d: x = %d\n", omp_get_thread_num(), x);
    }
}

void demonstrate_lastprivate_clause() {
    int x;
    #pragma omp parallel for lastprivate(x)
    for (int i = 0; i < 5; i++) {
        x = i;
        printf("Thread %d processes iteration %d\n", omp_get_thread_num(), i);
    }
    printf("Last value of x: %d\n", x);
}

void demonstrate_single_directive() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Single directive executed by thread %d\n", omp_get_thread_num());
        }
    }
}

void demonstrate_barrier_directive() {
    #pragma omp parallel
    {
        printf("Thread %d reached the barrier.\n", omp_get_thread_num());
        #pragma omp barrier
        printf("Thread %d passed the barrier.\n", omp_get_thread_num());
    }
}

void demonstrate_atomic_directive() {
    int sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        #pragma omp atomic
        sum += i;
    }
    printf("Sum of first 10 integers: %d\n", sum);
}

int main() {
    int choice;

    printf("Select a directive/clause to demonstrate:\n");
    printf("1. Parallel For Directive\n");
    printf("2. Private Clause\n");
    printf("3. Shared Clause\n");
    printf("4. Critical Directive\n");
    printf("5. Master Directive\n");
    printf("6. Threadprivate Clause\n");
    printf("7. Default Clause\n");
    printf("8. Firstprivate Clause\n");
    printf("9. Lastprivate Clause\n");
    printf("10. Single Directive\n");
    printf("11. Barrier Directive\n");
    printf("12. Atomic Directive\n");
    printf("Enter your choice (1-12): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: demonstrate_parallel_for(); break;
        case 2: demonstrate_private_clause(); break;
        case 3: demonstrate_shared_clause(); break;
        case 4: demonstrate_critical_directive(); break;
        case 5: demonstrate_master_directive(); break;
        case 6: demonstrate_threadprivate_clause(); break;
        case 7: demonstrate_default_clause(); break;
        case 8: demonstrate_firstprivate_clause(); break;
        case 9: demonstrate_lastprivate_clause(); break;
        case 10: demonstrate_single_directive(); break;
        case 11: demonstrate_barrier_directive(); break;
        case 12: demonstrate_atomic_directive(); break;
        default: printf("Invalid choice. Please select a valid option.\n");
    }

    return 0;
}

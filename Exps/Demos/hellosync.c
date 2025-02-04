#include <stdio.h>
#include <omp.h>

int main() {
    int total_prints = 100;

    omp_set_num_threads(omp_get_max_threads());


    #pragma omp parallel for ordered
    for (int i = 0; i < total_prints; i++) {
        #pragma omp ordered
        {
            int thread_id = omp_get_thread_num();
            printf("Hello, World! from thread %d: print %d out of %d.\n", thread_id, i + 1, total_prints);
        }
    }

    return 0;
}

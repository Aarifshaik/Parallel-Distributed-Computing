#include <stdio.h>
#include <omp.h>

int main() {
    int total_prints=100;
    omp_set_num_threads(omp_get_max_threads());


    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();  
        
        // printf("Hello, World! from thread %d out of %d threads.\n", thread_id, total_threads);

        for(int i=thread_id; i<total_prints; i+=total_threads){
            printf("%d Hello, World! from thread %d out of %d threads. \n", i,thread_id, total_threads);
        }
    }

    return 0;
}

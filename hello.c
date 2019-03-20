#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    
    int thread_count;

    if (argc > 1) {
        thread_count = strtol(argv[1], NULL, 10);
    } else {
        thread_count = omp_get_num_procs();
    }
    
    omp_set_num_threads(thread_count);

    #pragma omp parallel
    printf("Hello from thread %d\n", 
        omp_get_thread_num());
    
    return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    
    unsigned long long k;
    unsigned long long n = strtol(argv[1], NULL, 10);
    
    double factor = 1.0;
    double sum = 0.0;
    
    int thread_count;
    
    if (argc > 2) {
        thread_count = strtol(argv[2], NULL, 10);
    } else {
        thread_count = omp_get_num_procs();
    }
    
    omp_set_num_threads(thread_count);
    
    double starttime = omp_get_wtime();
    
    #pragma omp parallel for \
        default(none) private(k, factor) shared(n) \
        reduction(+:sum)
    for (k = 0; k < n; k++) {
        
        if (k % 2 == 0) {
            factor = 1.0;
        } else {
            factor = -1.0;
        }
        
        sum += factor/(2*k+1);
        
    }
    
    sum *= 4;
    
    double endtime = omp_get_wtime();
    
    printf("Pi approximation: %.20e (%.3e seconds)\n", 
        sum, endtime-starttime);
        
    return 0;

}

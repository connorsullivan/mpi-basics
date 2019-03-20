#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    
    double starttime, endtime;
    double result = 0.0;
    double a = 0.0;
    double b = 1.0;
    double h, x;
    int i, n;
    int thread_count;
    
    if (argc > 1) {
        thread_count = strtol(argv[1], NULL, 10);
    } else {
        thread_count = omp_get_num_procs();
    }
    omp_set_num_threads(thread_count);

    printf("Number of trapezoids: ");
    scanf("%d", &n);
    
    h = (b-a)/n;
    
    starttime = omp_get_wtime();
    
    #pragma omp parallel for private(x) reduction(+:result)
    for (i = 0; i < n; i++) {
        x = (i + 0.5) * h;
        result += 4.0/(1.0 + x*x);
    }
    result *= h;
    
    endtime = omp_get_wtime();
    
    printf("%.11e (%.9f seconds)\n", result, endtime-starttime);
        
    return 0;

}

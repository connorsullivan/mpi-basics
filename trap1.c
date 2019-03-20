#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Trap(double a, double b, int n, double *global_result_p);
double f(double x);

int main(int argc, char *argv[]) {
    
    double starttime, endtime;
    double global_result = 0.0;
    double a = 0.0;
    double b = 1.0;
    int n;
    int thread_count;
    
    if (argc > 1) {
        thread_count = strtol(argv[1], NULL, 10);
    } else {
        thread_count = 4;
    }

    printf("Number of trapezoids: ");
    scanf("%d", &n);
    
    starttime = omp_get_wtime();
    
    #pragma omp parallel num_threads(thread_count)
    Trap(a, b, n, &global_result);
    
    endtime = omp_get_wtime();
    
    printf("%.11e (%.9f seconds)\n", global_result, endtime-starttime);
        
    return 0;

}

void Trap(double a, double b, int n, double *global_result) {
 
    double h, x, my_result;
    double local_a, local_b;
    int i, local_n;
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b-a)/n;
    
    local_n = n/thread_count;
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;

    my_result = (f(local_a) + f(local_b))/2.0;
    for (i = 1; i <= local_n-1; i++) {
        x = local_a + i*h;
        my_result += f(x);
    }
    my_result *= h;
 
    #pragma omp atomic
    *global_result += my_result;
 
}

double f(double x) {
    return 4.0/(1.0 + x*x);
}

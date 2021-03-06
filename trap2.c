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
 
    double h, x, sum;
    int i;
    int thread_num = omp_get_thread_num();
    int num_threads = omp_get_num_threads();

    h = (b-a)/n;
    
    for (i = thread_num; i < n; i = i + num_threads) {
        x = (i + 0.5) * h;
        sum += f(x);
    }
    sum *= h;
 
    #pragma omp atomic
    *global_result += sum;
 
}

double f(double x) {
    return 4.0/(1.0 + x*x);
}

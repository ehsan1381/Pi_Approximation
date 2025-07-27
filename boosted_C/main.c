#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <pthread.h>

// Thread structure for parallel computation
typedef struct {
    int N;
    int precision_mode;  // 0 = double, 1 = long double
    double result_d[2];
    long double result_ld[2];
    double time_ms;
} Computation;

void* compute_wrapper(void* arg) {
    Computation* comp = (Computation*)arg;
    clock_t start = clock();
    
    if (comp->precision_mode == 0) {
        // Double precision
        find_optimal_lambda(comp->N, 0.1, 1.0, 1e-15, comp->result_d);
    } else {
        // Long double precision
        find_optimal_lambdaLD(comp->N, 0.1L, 1.0L, 1e-18L, comp->result_ld);
    }
    
    comp->time_ms = 1000.0 * (clock() - start) / CLOCKS_PER_SEC;
    return NULL;
}

int main() {
    // Configure computation parameters
    int term_counts[] = {100, 120, 140, 160, 180, 200};
    int num_terms = sizeof(term_counts)/sizeof(term_counts[0]);
    int precision_mode = 1;  // 0 = double, 1 = long double
    
    // Create computation tasks
    Computation tasks[num_terms];
    pthread_t threads[num_terms];
    
    // Start parallel computations
    for (int i = 0; i < num_terms; i++) {
        tasks[i].N = term_counts[i];
        tasks[i].precision_mode = precision_mode;
        pthread_create(&threads[i], NULL, compute_wrapper, &tasks[i]);
    }
    
    // Wait for completion
    for (int i = 0; i < num_terms; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Output results
    FILE* fp = fopen("results.txt", "w");
    fprintf(fp, "Terms\tLambda\t\t\tError\t\t\tTime(ms)\n");
    
    for (int i = 0; i < num_terms; i++) {
        if (precision_mode == 0) {
            printf("N=%d: λ=%.15f, Error=%.3e, Time=%.2fms\n",
                   tasks[i].N, tasks[i].result_d[0], 
                   tasks[i].result_d[1], tasks[i].time_ms);
            fprintf(fp, "%d\t%.15f\t%.3e\t%.2f\n", 
                   tasks[i].N, tasks[i].result_d[0], 
                   tasks[i].result_d[1], tasks[i].time_ms);
        } else {
            printf("N=%d: λ=%.15Lf, Error=%.3Le, Time=%.2fms\n",
                   tasks[i].N, tasks[i].result_ld[0], 
                   tasks[i].result_ld[1], tasks[i].time_ms);
            fprintf(fp, "%d\t%.15Lf\t%.3Le\t%.2f\n", 
                   tasks[i].N, tasks[i].result_ld[0], 
                   tasks[i].result_ld[1], tasks[i].time_ms);
        }
    }
    
    fclose(fp);
    return 0;
}
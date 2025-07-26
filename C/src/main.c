#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Test parameters
    int term_counts[] = {88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
    int num_terms = sizeof(term_counts) / sizeof(term_counts[0]);

    FILE *fp = fopen("lambda_optimization_data.txt", "w");
    if (!fp) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Compute and save results
    for (int i = 0; i < num_terms; i++) {
        int N = term_counts[i];
        double result[2];
        find_optimal_lambda(N, 0.1, 1.0, 1e-10, result);
        
        printf("N=%d: Optimal λ=%.12f, Error=%.10e\n", 
               N, result[0], result[1]);
        fprintf(fp, "%d %.12f %.10e\n", N, result[0], result[1]);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
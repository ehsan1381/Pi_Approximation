// July 2025 , by Celestine1729
// Upgraded to use quad-precision floating point
#include "functions.h"
#include <quadmath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Test parameters
    int term_counts[] = {88, 89, 90, 91, 92, 93, 94, 95, 96, 97};
    int num_terms = sizeof(term_counts) / sizeof(term_counts[0]);

    FILE *fp = fopen("lambda_optimization_data.txt", "w");
    if (!fp) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Compute and save results
    for (int i = 0; i < num_terms; i++) {
        int N = term_counts[i];
        __float128 result[2];
        find_optimal_lambda(N, 0.1Q, 1.0Q, 1e-30Q, result);  // Tighter tolerance
        
        // Convert quad values to strings
        char lambda_str[128], error_str[128];
        quadmath_snprintf(lambda_str, sizeof(lambda_str), "%.35Qf", result[0]);
        quadmath_snprintf(error_str, sizeof(error_str), "%.35Qe", result[1]);

        printf("N=%d: Optimal λ=%s, Error=%s\n", N, lambda_str, error_str);
        fprintf(fp, "%d %s %s\n", N, lambda_str, error_str);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
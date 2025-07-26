#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITER 200

// Calculate 1/num! with bounds check
double OneOverFactorial(int num) {
    if (num > 170) {
        fprintf(stderr, "Error: Input too large for 1/n! calculation\n");
        exit(EXIT_FAILURE);
    }

    double result = 1.0;
    for (int i = 1; i <= num; i++) {
        result /= i;
    }
    return result;
}

// Compute rising factorial (x)_n
double RisingFactorial(double x, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++) {
        result *= (x + i);
    }
    return result;
}

// Precompute 1/n! for n=1 to num
double* FactorialArray(int num) {
    double* arr = (double*)malloc(num * sizeof(double));
    if (!arr) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < num; i++) {
        arr[i] = OneOverFactorial(i + 1);
    }
    return arr;
}

// Compute π approximation using series
double Execute(double Lambda, int NTerms, double* Factorials) {
    double total_sum = 0.0;
    for (int n = 1; n <= NTerms; n++) {
        double fact = Factorials[n - 1];
        double first_term = 1.0 / (n + Lambda) - 4.0 / (2 * n + 1);
        double a_n = pow(2 * n + 1, 2) / (4.0 * (n + Lambda)) - n;
        double poch_val = RisingFactorial(a_n, n);
        total_sum += fact * first_term * poch_val;
    }
    return 4.0 + total_sum;
}

// Find optimal λ via bisection method
void find_optimal_lambda(int N, double lambda_low, double lambda_high, double tol, double* result) {
    double* fact_array = FactorialArray(N);
    double f_low = Execute(lambda_low, N, fact_array) - M_PI;
    double f_high = Execute(lambda_high, N, fact_array) - M_PI;

    // Validate bracket
    if (f_low * f_high > 0) {
        for (int i = 0; i < 20; i++) {
            double test_point = lambda_low + i * (lambda_high - lambda_low) / 19.0;
            double f_test = Execute(test_point, N, fact_array) - M_PI;
            if (f_low * f_test < 0) {
                lambda_high = test_point;
                f_high = f_test;
                break;
            }
        }
    }

    // Bisection loop
    double lam_mid = 0.0, f_mid = 0.0;
    for (int iter = 0; iter < MAX_ITER; iter++) {
        lam_mid = (lambda_low + lambda_high) / 2.0;
        f_mid = Execute(lam_mid, N, fact_array) - M_PI;

        if (fabs(f_mid) < tol) break;

        if (f_mid * f_low < 0) {
            lambda_high = lam_mid;
            f_high = f_mid;
        } else {
            lambda_low = lam_mid;
            f_low = f_mid;
        }
    }

    result[0] = lam_mid;
    result[1] = fabs(f_mid);
    free(fact_array);
}
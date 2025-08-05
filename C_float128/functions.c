// July 2025 , by Celestine 
// functions for computing PI, translated from python
// upgraded to use quad-precision (__float128)
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <quadmath.h>

#ifndef M_PIq
#define M_PIq 3.14159265358979323846264338327950288419716939937510Q
#endif

#define MAX_ITER 400  // Increased for quad precision convergence

// Calculate 1/num! with bounds check
__float128 OneOverFactorial(int num) {
    if (num > 10000) {  // Increased limit for quad precision
        fprintf(stderr, "Error: Input too large for 1/n! calculation\n");
        exit(EXIT_FAILURE);
    }

    __float128 result = 1.0Q;
    for (int i = 1; i <= num; i++) {
        result /= i;
    }
    return result;
}

// Compute rising factorial (x)_n
__float128 RisingFactorial(__float128 x, int n) {
    __float128 result = 1.0Q;
    for (int i = 0; i < n; i++) {
        result *= (x + i);
    }
    return result;
}

// Precompute 1/n! for n=1 to num
__float128* FactorialArray(int num) {
    __float128* arr = (__float128*)malloc(num * sizeof(__float128));
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
__float128 Execute(__float128 Lambda, int NTerms, __float128* Factorials) {
    __float128 total_sum = 0.0Q;
    for (int n = 1; n <= NTerms; n++) {
        __float128 fact = Factorials[n - 1];
        __float128 first_term = 1.0Q / (n + Lambda) - 4.0Q / (2 * n + 1);
        __float128 a_n = powq(2 * n + 1, 2) / (4.0Q * (n + Lambda)) - n;
        __float128 poch_val = RisingFactorial(a_n, n);
        total_sum += fact * first_term * poch_val;
    }
    return 4.0Q + total_sum;
}

// Find optimal λ via bisection method
void find_optimal_lambda(int N, __float128 lambda_low, __float128 lambda_high, 
                         __float128 tol, __float128* result) {
    __float128* fact_array = FactorialArray(N);
    __float128 f_low = Execute(lambda_low, N, fact_array) - M_PIq;
    __float128 f_high = Execute(lambda_high, N, fact_array) - M_PIq;

    // Validate bracket
    if (signbitq(f_low) == signbitq(f_high)) {
        for (int i = 0; i < 20; i++) {
            __float128 test_point = lambda_low + i * (lambda_high - lambda_low) / 19.0Q;
            __float128 f_test = Execute(test_point, N, fact_array) - M_PIq;
            if (signbitq(f_low) != signbitq(f_test)) {
                lambda_high = test_point;
                f_high = f_test;
                break;
            }
        }
    }

    // Bisection loop
    __float128 lam_mid = 0.0Q, f_mid = 0.0Q;
    for (int iter = 0; iter < MAX_ITER; iter++) {
        lam_mid = (lambda_low + lambda_high) / 2.0Q;
        f_mid = Execute(lam_mid, N, fact_array) - M_PIq;

        if (fabsq(f_mid) < tol) break;

        if (signbitq(f_mid) != signbitq(f_low)) {
            lambda_high = lam_mid;
            f_high = f_mid;
        } else {
            lambda_low = lam_mid;
            f_low = f_mid;
        }
    }

    result[0] = lam_mid;
    result[1] = fabsq(f_mid);
    free(fact_array);
}
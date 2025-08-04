// August 2025 , by Clestine1729
// contact: celestine1729@proton.me
// This file is part of the Boost library for high precision calculations.
// It implements various mathematical functions using Boost's multiprecision library.
// the funcs are designed to handle high precision calculations, particularly for π approximation and optimization of λ.

#include "functions_boost.h"
#include <iostream>
#include <vector>
#include <boost/math/constants/constants.hpp>
#include <cstdlib> // For exit()

// Calculate π with full precision of mp_float
mp_float calculate_pi() {
    return boost::math::constants::pi<mp_float>();
}

mp_float OneOverFactorial(int num) {
    if (num > 10000) {
        std::cerr << "Error: Input too large for 1/n! calculation\n";
        exit(EXIT_FAILURE);
    }

    mp_float result = 1.0;
    for (int i = 1; i <= num; i++) {
        result /= i;
    }
    return result;
}

mp_float RisingFactorial(const mp_float& x, int n) {
    mp_float result = 1.0;
    for (int i = 0; i < n; i++) {
        result *= (x + i);
    }
    return result;
}

std::vector<mp_float> FactorialArray(int num) {
    std::vector<mp_float> arr;
    arr.reserve(num);
    
    for (int i = 0; i < num; i++) {
        arr.push_back(OneOverFactorial(i + 1));
    }
    return arr;
}

mp_float Execute(const mp_float& Lambda, int NTerms, const std::vector<mp_float>& Factorials) {
    mp_float total_sum = 0.0;
    for (int n = 1; n <= NTerms; n++) {
        const mp_float& fact = Factorials[n - 1];
        mp_float first_term = 1.0 / (n + Lambda) - 4.0 / (2 * n + 1);
        mp_float base = mp_float(2 * n + 1);
        mp_float a_n = boost::multiprecision::pow(base, 2) / (4.0 * (n + Lambda)) - n;
        mp_float poch_val = RisingFactorial(a_n, n);
        total_sum += fact * first_term * poch_val;
    }
    return 4.0 + total_sum;
}

void find_optimal_lambda(int N, const mp_float& lambda_low_in, const mp_float& lambda_high_in, 
                         const mp_float& tol, mp_float result[2]) {
    const mp_float PI = calculate_pi();
    std::vector<mp_float> fact_array = FactorialArray(N);

    mp_float lambda_low = lambda_low_in;
    mp_float lambda_high = lambda_high_in;
    mp_float f_low = Execute(lambda_low, N, fact_array) - PI;
    mp_float f_high = Execute(lambda_high, N, fact_array) - PI;

    // Validate bracket
    if (f_low * f_high > 0) {
        for (int i = 0; i < 20; i++) {
            mp_float test_point = lambda_low_in + i * (lambda_high_in - lambda_low_in) / 19.0;
            mp_float f_test = Execute(test_point, N, fact_array) - PI;
            if (f_low * f_test < 0) {
                lambda_high = test_point;
                f_high = f_test;
                break;
            }
            if (f_high * f_test < 0) {
                lambda_low = test_point;
                f_low = f_test;
                break;
            }
        }
    }

    // Bisection loop
    const int MAX_ITER = 400;
    mp_float lam_mid = 0, f_mid = 0;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        lam_mid = (lambda_low + lambda_high) / 2.0;
        f_mid = Execute(lam_mid, N, fact_array) - PI;

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
}
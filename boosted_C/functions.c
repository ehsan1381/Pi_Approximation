#include "functions.h"
#include <stdio.h>
#include <float.h>
#include <math.h>

// ================= DOUBLE PRECISION =================

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

double RisingFactorial(double x, int n) {
    double result = 1.0;
    for (int i = 0; i < n; i++) {
        result *= (x + i);
        // Prevent overflow using exponent scaling
        if (fabs(result) > 1e100) {
            result *= 1e-100;
        }
    }
    return result;
}

double* FactorialArray(int num) {
    double* arr = malloc(num * sizeof(double));
    if (!arr) return NULL;
    
    double current = 1.0;
    for (int i = 0; i < num; i++) {
        current /= (i + 1);
        arr[i] = current;
    }
    return arr;
}

double Execute(double Lambda, int NTerms, double* Factorials) {
    double total_sum = 0.0;
    double carry = 0.0;  // Kahan summation compensation
    
    for (int n = 1; n <= NTerms; n++) {
        const double n_plus_lambda = n + Lambda;
        const double two_n_plus_one = 2 * n + 1;
        
        double first_term = 1.0 / n_plus_lambda - 4.0 / two_n_plus_one;
        double a_n = (two_n_plus_one * two_n_plus_one) / 
                    (4.0 * n_plus_lambda) - n;
        
        double poch_val = RisingFactorial(a_n, n);
        double term = Factorials[n-1] * first_term * poch_val;
        
        // Kahan summation
        double y = term - carry;
        double t = total_sum + y;
        carry = (t - total_sum) - y;
        total_sum = t;
        
        // Early termination for negligible terms
        if (fabs(term) < DBL_EPSILON * fabs(total_sum)) {
            break;
        }
    }
    return 4.0 + total_sum;
}

// Brent's method for root finding
void find_optimal_lambda(int N, double lambda_low, double lambda_high, 
                         double tol, double* result) {
    double* fact_array = FactorialArray(N);
    if (!fact_array) return;
    
    // Target function
    double (*f)(double) = [=](double lam) -> double {
        return Execute(lam, N, fact_array) - M_PI;
    };
    
    // Brent's method implementation
    double a = lambda_low, b = lambda_high;
    double fa = f(a), fb = f(b);
    
    if (fa * fb >= 0) {
        // Fallback to bisection
        for (int i = 0; i < 100; i++) {
            double mid = (a + b) / 2.0;
            double fmid = f(mid);
            
            if (fabs(fmid) < tol) {
                result[0] = mid;
                result[1] = fabs(fmid);
                free(fact_array);
                return;
            }
            
            if (fmid * fa < 0) {
                b = mid;
                fb = fmid;
            } else {
                a = mid;
                fa = fmid;
            }
        }
    }
    
    double c = a, fc = fa;
    double d = b - a, e = d;
    
    for (int iter = 0; iter < 100; iter++) {
        if (fb * fc > 0) { c = a; fc = fa; d = b - a; e = d; }
        if (fabs(fc) < fabs(fb)) { a = b; b = c; c = a; fa = fb; fb = fc; fc = fa; }
        
        double tol1 = 2 * DBL_EPSILON * fabs(b) + tol/2;
        double xm = (c - b)/2;
        
        if (fabs(xm) <= tol1 || fb == 0.0) break;
        
        if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {
            // Inverse quadratic interpolation
            double s = fb/fa;
            double p, q;
            if (a == c) {
                p = 2 * xm * s;
                q = 1 - s;
            } else {
                q = fa/fc;
                double r = fb/fc;
                p = s * (2 * xm * q * (q - r) - (b - a) * (r - 1));
                q = (q - 1) * (r - 1) * (s - 1);
            }
            if (p > 0) q = -q;
            p = fabs(p);
            if (2*p < fmin(3*xm*q - fabs(tol1*q), fabs(e*q))) {
                e = d;
                d = p/q;
            } else {
                d = xm;
                e = d;
            }
        } else {
            d = xm;
            e = d;
        }
        a = b;
        fa = fb;
        if (fabs(d) > tol1) b += d;
        else b += (xm > 0 ? fabs(tol1) : -fabs(tol1));
        fb = f(b);
    }
    
    result[0] = b;
    result[1] = fabs(fb);
    free(fact_array);
}

// ================= LONG DOUBLE PRECISION =================

long double OneOverFactorialLD(int num) {
    if (num > 1754) {  // Higher limit for long double
        return 0.0L;
    }
    
    long double result = 1.0L;
    for (int i = 1; i <= num; i++) {
        result /= i;
    }
    return result;
}

long double RisingFactorialLD(long double x, int n) {
    long double result = 1.0L;
    for (int i = 0; i < n; i++) {
        result *= (x + i);
        // Prevent overflow using exponent scaling
        if (fabsl(result) > 1e100L) {
            result *= 1e-100L;
        }
    }
    return result;
}

long double* FactorialArrayLD(int num) {
    long double* arr = malloc(num * sizeof(long double));
    if (!arr) return NULL;
    
    long double current = 1.0L;
    for (int i = 0; i < num; i++) {
        current /= (i + 1);
        arr[i] = current;
    }
    return arr;
}

long double ExecuteLD(long double Lambda, int NTerms, long double* Factorials) {
    long double total_sum = 0.0L;
    long double carry = 0.0L;  // Kahan compensation
    
    for (int n = 1; n <= NTerms; n++) {
        const long double n_plus_lambda = n + Lambda;
        const long double two_n_plus_one = 2 * n + 1;
        
        long double first_term = 1.0L / n_plus_lambda - 4.0L / two_n_plus_one;
        long double a_n = (two_n_plus_one * two_n_plus_one) / 
                         (4.0L * n_plus_lambda) - n;
        
        long double poch_val = RisingFactorialLD(a_n, n);
        long double term = Factorials[n-1] * first_term * poch_val;
        
        // Kahan summation
        long double y = term - carry;
        long double t = total_sum + y;
        carry = (t - total_sum) - y;
        total_sum = t;
        
        // Early termination
        if (fabsl(term) < LDBL_EPSILON * fabsl(total_sum)) {
            break;
        }
    }
    return 4.0L + total_sum;
}

void find_optimal_lambdaLD(int N, long double lambda_low, 
                          long double lambda_high, long double tol, 
                          long double* result) {
    long double* fact_array = FactorialArrayLD(N);
    if (!fact_array) return;
    
    // Target function
    long double (*f)(long double) = [=](long double lam) -> long double {
        return ExecuteLD(lam, N, fact_array) - (long double)M_PI;
    };
    
    // Brent's method
    long double a = lambda_low, b = lambda_high;
    long double fa = f(a), fb = f(b);
    
    if (fa * fb >= 0) {
        // Fallback to bisection
        for (int i = 0; i < 100; i++) {
            long double mid = (a + b) / 2.0L;
            long double fmid = f(mid);
            
            if (fabsl(fmid) < tol) {
                result[0] = mid;
                result[1] = fabsl(fmid);
                free(fact_array);
                return;
            }
            
            if (fmid * fa < 0) {
                b = mid;
                fb = fmid;
            } else {
                a = mid;
                fa = fmid;
            }
        }
    }
    
    long double c = a, fc = fa;
    long double d = b - a, e = d;
    
    for (int iter = 0; iter < 100; iter++) {
        if (fb * fc > 0) { c = a; fc = fa; d = b - a; e = d; }
        if (fabsl(fc) < fabsl(fb)) { a = b; b = c; c = a; fa = fb; fb = fc; fc = fa; }
        
        long double tol1 = 2 * LDBL_EPSILON * fabsl(b) + tol/2;
        long double xm = (c - b)/2;
        
        if (fabsl(xm) <= tol1 || fb == 0.0L) break;
        
        if (fabsl(e) >= tol1 && fabsl(fa) > fabsl(fb)) {
            // Inverse quadratic interpolation
            long double s = fb/fa;
            long double p, q;
            if (a == c) {
                p = 2 * xm * s;
                q = 1 - s;
            } else {
                q = fa/fc;
                long double r = fb/fc;
                p = s * (2 * xm * q * (q - r) - (b - a) * (r - 1));
                q = (q - 1) * (r - 1) * (s - 1);
            }
            if (p > 0) q = -q;
            p = fabsl(p);
            if (2*p < fminl(3*xm*q - fabsl(tol1*q), fabsl(e*q))) {
                e = d;
                d = p/q;
            } else {
                d = xm;
                e = d;
            }
        } else {
            d = xm;
            e = d;
        }
        a = b;
        fa = fb;
        if (fabsl(d) > tol1) b += d;
        else b += (xm > 0 ? fabsl(tol1) : -fabsl(tol1));
        fb = f(b);
    }
    
    result[0] = b;
    result[1] = fabsl(fb);
    free(fact_array);
}

// ================= HIGH-PRECISION UTILITIES =================

DoubleDouble dd_add(DoubleDouble a, DoubleDouble b) {
    double s1 = a.value + b.value;
    double v = s1 - a.value;
    double s2 = (a.value - (s1 - v)) + (b.value - v);
    double err = a.error + b.error + s2;
    return (DoubleDouble){s1, err};
}

DoubleDouble dd_mul(DoubleDouble a, DoubleDouble b) {
    double p1 = a.value * b.value;
    double p2 = a.value * b.error + a.error * b.value + a.error * b.error;
    return (DoubleDouble){p1, p2};
}
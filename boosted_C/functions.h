#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <math.h>
#include <stdlib.h>

// Define M_PI for portability
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Double precision functions
double OneOverFactorial(int num);
double RisingFactorial(double x, int n);
double* FactorialArray(int num);
double Execute(double Lambda, int NTerms, double* Factorials);
void find_optimal_lambda(int N, double lambda_low, double lambda_high, 
                         double tol, double* result);

// Long double precision functions
long double OneOverFactorialLD(int num);
long double RisingFactorialLD(long double x, int n);
long double* FactorialArrayLD(int num);
long double ExecuteLD(long double Lambda, int NTerms, long double* Factorials);
void find_optimal_lambdaLD(int N, long double lambda_low, 
                          long double lambda_high, long double tol, 
                          long double* result);

// High-precision utilities
typedef struct {
    double value;
    double error;
} DoubleDouble;

DoubleDouble dd_add(DoubleDouble a, DoubleDouble b);
DoubleDouble dd_mul(DoubleDouble a, DoubleDouble b);

#endif
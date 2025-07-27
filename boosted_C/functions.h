// July 2025 , by Celestine1729
// header file for the C translation, the code approximates the PI
// These funcs come from a reently found method for approximating PI
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <quadmath.h>

__float128 OneOverFactorial(int num);
__float128 RisingFactorial(__float128 x, int n);
__float128* FactorialArray(int num);
__float128 Execute(__float128 Lambda, int NTerms, __float128* Factorials);
void find_optimal_lambda(int N, __float128 lambda_low, __float128 lambda_high, 
                         __float128 tol, __float128* result);

#endif
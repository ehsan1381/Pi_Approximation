// July 2025 , by Celestine1729
// header file for the C translation, the code approximates the PI
// These funcs come from a reently found method for approximating PI
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double OneOverFactorial(int num);
double RisingFactorial(double x, int n);
double* FactorialArray(int num);
double Execute(double Lambda, int NTerms, double* Factorials);
void find_optimal_lambda(int N, double lambda_low, double lambda_high, double tol, double* result);

#endif
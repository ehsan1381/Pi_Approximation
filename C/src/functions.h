#ifndef FUNCTIONS_H
#define FUNCTIONS_H

double OneOverFactorial(int num);
double RisingFactorial(double x, int n);
double* FactorialArray(int num);
double Execute(double Lambda, int NTerms, double* Factorials);
void find_optimal_lambda(int N, double lambda_low, double lambda_high, double tol, double* result);

#endif
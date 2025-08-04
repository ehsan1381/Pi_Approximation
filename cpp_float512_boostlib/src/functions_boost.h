#ifndef FUNCTIONS_BOOST_H
#define FUNCTIONS_BOOST_H

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <vector>

// Define our multiprecision float type with 150-digit precision (≈512 bits)
using mp_float = boost::multiprecision::cpp_dec_float_150;

// Function declarations
mp_float OneOverFactorial(int num);
mp_float RisingFactorial(const mp_float& x, int n);
std::vector<mp_float> FactorialArray(int num);
mp_float Execute(const mp_float& Lambda, int NTerms, const std::vector<mp_float>& Factorials);
void find_optimal_lambda(int N, const mp_float& lambda_low, const mp_float& lambda_high, 
                         const mp_float& tol, mp_float result[2]);

// Calculate π to high precision
const mp_float calculate_pi();

#endif
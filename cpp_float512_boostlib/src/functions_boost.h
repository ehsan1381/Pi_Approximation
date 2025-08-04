// functions_boost.h
// August 2025, by Clestine1729
// contact:celestine172@proton.me
// This file is part of the Boost library for high precision calculations.
// It implements various mathematical functions using Boost's multiprecision library.
// The functions are designed to handle high precision calculations, particularly for π approximation and optimization of λ.
// The method for approximation of π involves calculating the optimal value of λ using a bisection method
// It is a newly found method for Pi approximation and high precision calculations.
#ifndef FUNCTIONS_BOOST_H
#define FUNCTIONS_BOOST_H

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <vector>

// Define our multiprecision float type with 150-digit precision (≈512 bits)
using mp_float = boost::multiprecision::number<boost::multiprecision::cpp_dec_float<150>>;

// Function declarations
mp_float OneOverFactorial(int num);
mp_float RisingFactorial(const mp_float& x, int n);
std::vector<mp_float> FactorialArray(int num);
mp_float Execute(const mp_float& Lambda, int NTerms, const std::vector<mp_float>& Factorials);
void find_optimal_lambda(int N, const mp_float& lambda_low, const mp_float& lambda_high, 
                         const mp_float& tol, mp_float result[2]);

// Calculate π with full precision of mp_float
mp_float calculate_pi();

#endif
# This script calculates the Pochhammer symbol and Stirling numbers of the first kind.
# It also computes the factorial of numbers and prepares polynomial arrays.

import numpy as np
import sys
import math
from functools import lru_cache

def OneOverFactorial(num):
    """
    Calculates the value of 1 divided by the factorial of a given number.
    """
    if num > 170:  # Reduced from 177 for better numerical stability
        print("Error: Input is too large to calculate 1/n! within float precision")
        sys.exit()

    result = 1.0
    for i in range(1, num + 1):
        result /= i
    return result

@lru_cache(maxsize=None)
def StirlingNumberOfFirstKind(n, k):
    """
    Calculate the unsigned Stirling number of the first kind, c(n, k).
    Uses memoization for efficiency.
    """
    if n == k:
        return 1
    if k == 0 or n == 0:
        return 0
    return (n - 1) * StirlingNumberOfFirstKind(n - 1, k) + StirlingNumberOfFirstKind(n - 1, k - 1)

def RisingFactorial(x, n):
    """
    Directly computes the rising factorial (Pochhammer symbol) (x)_n
    """
    result = 1.0
    for i in range(n):
        result *= (x + i)
    return result

def FactorialArray(num):
    """
    Precomputes 1/n! for n=1 to num
    """
    arr = np.zeros(num)
    for i in range(num):
        arr[i] = OneOverFactorial(i + 1)
    return arr

def Execute(Lambda, NTerms, Factorials):
    """
    Computes the pi approximation using the series:
    π ≈ 4 + Σ [ (1/n!) * (1/(n+λ) - 4/(2n+1)) * (a_n)_n ]
    where a_n = (2n+1)^2/(4(n+λ)) - n
    """
    total_sum = 0.0
    
    for n in range(1, NTerms + 1):
        # Compute components
        fact = Factorials[n - 1]  # 1/n!
        first_term = 1 / (n + Lambda) - 4 / (2 * n + 1)
        a_n = (2 * n + 1) ** 2 / (4 * (n + Lambda)) - n
        
        # Compute rising factorial directly
        poch_val = RisingFactorial(a_n, n)
        
        # Compute term and accumulate
        term = fact * first_term * poch_val
        total_sum += term

    PI_approx = 4.0 + total_sum
    return PI_approx

    
def find_optimal_lambda(N, lambda_low=0.1, lambda_high=1.0, tol=1e-10):
    """
    Finds optimal λ using bisection method for fixed N
    Returns: (optimal_lambda, error)
    """
    fact_array = FactorialArray(N)
    
    def error_func(lam):
        approx = Execute(lam, N, fact_array)
        return approx - math.pi
    
    # Ensure we have a root bracket
    f_low = error_func(lambda_low)
    f_high = error_func(lambda_high)
    
    if f_low * f_high > 0:
        # Try to find a valid bracket automatically
        test_points = np.linspace(0.1, 1.0, 20)
        for i in range(len(test_points)-1):
            f1 = error_func(test_points[i])
            f2 = error_func(test_points[i+1])
            if f1 * f2 < 0:
                lambda_low, lambda_high = test_points[i], test_points[i+1]
                break
    
    # Bisection algorithm
    for _ in range(200):  # Max iterations
        lam_mid = (lambda_low + lambda_high) / 2
        f_mid = error_func(lam_mid)
        
        if abs(f_mid) < tol:
            break
            
        if f_mid * error_func(lambda_low) < 0:
            lambda_high = lam_mid
        else:
            lambda_low = lam_mid
    
    return lam_mid, abs(f_mid)

# Test optimization for different term counts
if __name__ == '__main__':
    term_counts = [88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100]
    results = {}
    
    for N in term_counts:
        lambda_opt, error = find_optimal_lambda(N)
        results[N] = (lambda_opt, error)
        print(f"N={N}: Optimal λ={lambda_opt:.12f}, Error={error:.10e}")
    
    # Plot results
    lambdas = [results[N][0] for N in term_counts]
    errors = [results[N][1] for N in term_counts]
    
    import matplotlib.pyplot as plt
    plt.figure(figsize=(10, 5))
    
    plt.subplot(1, 2, 1)
    plt.plot(term_counts, lambdas, 'o-')
    plt.xlabel('Number of Terms (N)')
    plt.ylabel('Optimal λ')
    plt.title('Optimal λ vs Term Count')
    
    plt.subplot(1, 2, 2)
    plt.semilogy(term_counts, errors, 's-')
    plt.xlabel('Number of Terms (N)')
    plt.ylabel('Error')
    plt.title('Approximation Error at Optimal λ')
    
    plt.tight_layout()
    plt.savefig('lambda_optimization.png')
    plt.show()
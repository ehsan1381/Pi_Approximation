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

if __name__ == '__main__':
    # Test parameters
    test_lambdas = [0.5, 1.0, 2.5, 10.0]
    test_terms = [5, 10, 20, 30]
    
    for lam in test_lambdas:
        print(f"\nTesting λ = {lam}")
        for n_terms in test_terms:
            # Precompute factorials
            fact_array = FactorialArray(n_terms)
            
            # Compute approximation
            try:
                pi_approx = Execute(lam, n_terms, fact_array)
                error = abs(pi_approx - math.pi)
                print(f"  N={n_terms}: Approx={pi_approx:.10f}, Error={error:.2e}")
            except Exception as e:
                print(f"  N={n_terms}: Failed ({str(e)})")

    # Recommended parameters
    print("\nRecommended parameters: λ=0.5-1.0 with N=20-30 terms")
# This script computes an approximation of π using a series expansion
# based on the Pochhammer symbol and Stirling numbers of the first kind.   
# It includes optimizations for factorial calculations, caching for Stirling numbers,
# and term-by-term monitoring to ensure convergence.
#TODO : first make a working version, then optimize it
#then add tests
#TODO : analyse each function and its performance
#TODO : add docstrings and comments for clarity

import numpy as np
import sys
import math
from functools import lru_cache

# Safe factorial calculation
def OneOverFactorial(n):
    if n > 170:
        return 0.0  # Beyond float precision
    result = 1.0
    for i in range(1, n+1):
        result /= i
    return result

# Stirling numbers with caching
@lru_cache(maxsize=None)
def Stirling(n, k):
    if n == k: return 1
    if k == 0 or n == 0: return 0
    return (n-1)*Stirling(n-1, k) + Stirling(n-1, k-1)

# Direct rising factorial calculation
def RisingFactorial(x, n):
    result = 1.0
    for i in range(n):
        result *= (x + i)
    return result

# Main computation with term monitoring
def compute_pi(Lambda, max_n):
    """
    Computes π approximation with term-by-term monitoring
    Returns: (approximation, term_details)
    """
    pi_approx = 4.0
    terms = []
    
    for n in range(1, max_n+1):
        # Compute components
        inv_fact = OneOverFactorial(n)
        term1 = 1/(n + Lambda) - 4/(2*n + 1)
        a_n = (2*n + 1)**2/(4*(n + Lambda)) - n
        poch = RisingFactorial(a_n, n)
        
        # Full term
        term_val = inv_fact * term1 * poch
        pi_approx += term_val
        
        # Store term details
        terms.append({
            'n': n,
            'inv_fact': inv_fact,
            'term1': term1,
            'a_n': a_n,
            'poch': poch,
            'term_val': term_val,
            'current_pi': pi_approx
        })
        
        # Stop when terms become negligible
        if abs(term_val) < 1e-16 * abs(pi_approx):
            break
    
    return pi_approx, terms

# Verification and analysis
def verify_convergence():
    results = {}
    for lam in [0.5, 0.6, 0.7, 0.8, 0.9, 1.0]:
        pi_approx, terms = compute_pi(lam, 30)
        error = abs(pi_approx - math.pi)
        results[lam] = {
            'approximation': pi_approx,
            'error': error,
            'terms': terms,
            'effective_terms': len(terms)
        }
        
        print(f"λ={lam}:")
        print(f"  Approx = {pi_approx:.16f}")
        print(f"  Error   = {error:.2e}")
        print(f"  Terms   = {len(terms)}")
        
        # Show term progression
        print("  Last 3 terms:")
        for t in terms[-3:]:
            print(f"    n={t['n']}: term={t['term_val']:.3e}, cum_pi={t['current_pi']:.16f}")
        print()
    
    return results

if __name__ == '__main__':
    print("Convergence Test for π Approximation")
    print("="*50)
    results = verify_convergence()
    
    # Optimal parameter recommendation
    best_lam = min(results, key=lambda x: results[x]['error'])
    print(f"\nOptimal λ: {best_lam} (Error={results[best_lam]['error']:.2e})")
    print(f"Use λ=0.5-1.0 with 15-20 terms for best results")
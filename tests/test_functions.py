# July 2025 , by Celestine_1729

import pytest
import numpy as np
import math
import sys
from functions import (OneOverFactorial, StirlingNumberOfFirstKind, 
                      RisingFactorial, FactorialArray, Execute, 
                      find_optimal_lambda)

# Disable sys.exit during tests
sys.exit = lambda code: None

## Test OneOverFactorial -----------------------------------------------------
@pytest.mark.parametrize("num, expected", [
    (0, 1.0),           # 0! = 1
    (1, 1.0),            # 1/1! = 1
    (5, 1/120),          # 1/5! = 1/120
    (10, 1/3628800),     # Valid input
    (170, 1/math.factorial(170)),  # Near limit
])
def test_OneOverFactorial_valid(num, expected):
    assert OneOverFactorial(num) == pytest.approx(expected, rel=1e-12)

def test_OneOverFactorial_large_input():
    with pytest.raises(SystemExit):
        OneOverFactorial(171)  # Should trigger exit

def test_OneOverFactorial_negative():
    with pytest.raises(SystemExit):
        OneOverFactorial(-1)

## Test StirlingNumberOfFirstKind --------------------------------------------
@pytest.mark.parametrize("n, k, expected", [
    (5, 5, 1),      # Base case: n == k
    (5, 0, 0),      # Base case: k == 0
    (0, 0, 0),      # Base case: n == 0
    (4, 2, 11),     # Known value
    (6, 3, 225),    # Known value
    (7, 1, 720),    # Known value
])
def test_StirlingNumberOfFirstKind(n, k, expected):
    assert StirlingNumberOfFirstKind(n, k) == expected

def test_Stirling_memoization():
    # First call should compute
    assert StirlingNumberOfFirstKind(8, 3) == 13068
    # Second call should use cache
    assert StirlingNumberOfFirstKind(8, 3) == 13068

def test_Stirling_invalid_input():
    with pytest.raises(RecursionError):
        StirlingNumberOfFirstKind(-1, 2)

## Test RisingFactorial ------------------------------------------------------
@pytest.mark.parametrize("x, n, expected", [
    (2, 0, 1.0),      # n=0 case
    (2, 1, 2.0),      # (2)_1 = 2
    (3, 4, 3*4*5*6),  # (3)_4 = 3×4×5×6
    (0.5, 3, 0.5*1.5*2.5),  # Fractional input
    (-2, 3, (-2)*(-1)*0),    # Negative input
])
def test_RisingFactorial(x, n, expected):
    assert RisingFactorial(x, n) == pytest.approx(expected, rel=1e-12)

## Test FactorialArray -------------------------------------------------------
def test_FactorialArray_size():
    arr = FactorialArray(5)
    assert len(arr) == 5
    assert arr[0] == pytest.approx(1.0)           # 1/1!
    assert arr[1] == pytest.approx(1/2)           # 1/2!
    assert arr[4] == pytest.approx(1/math.factorial(5))  # 1/5!

def test_FactorialArray_content():
    arr = FactorialArray(10)
    expected = [1/math.factorial(i+1) for i in range(10)]
    assert np.allclose(arr, expected, rtol=1e-12)

def test_FactorialArray_zero():
    arr = FactorialArray(0)
    assert len(arr) == 0

## Test Execute --------------------------------------------------------------
def test_Execute_basic():
    fact_array = FactorialArray(10)
    result = Execute(0.5, 5, fact_array)
    # Validate it's in reasonable pi range
    assert 3.0 < result < 3.2

def test_Execute_known_value():
    fact_array = FactorialArray(20)
    result = Execute(0.5, 20, fact_array)
    assert result == pytest.approx(math.pi, abs=1e-10)

def test_Execute_lambda_effects():
    fact_array = FactorialArray(10)
    result1 = Execute(0.1, 5, fact_array)
    result2 = Execute(0.9, 5, fact_array)
    assert result1 != result2

## Test find_optimal_lambda --------------------------------------------------
def test_find_optimal_lambda_convergence():
    optimal_lambda, error = find_optimal_lambda(20)
    assert 0.1 < optimal_lambda < 1.0
    assert error < 1e-10

def test_find_optimal_lambda_accuracy():
    optimal_lambda, error = find_optimal_lambda(50)
    pi_approx = Execute(optimal_lambda, 50, FactorialArray(50))
    assert abs(pi_approx - math.pi) < 1e-12

def test_find_optimal_lambda_invalid_bracket():
    # Should automatically find valid bracket
    optimal_lambda, error = find_optimal_lambda(
        20, 
        lambda_low=10.0, 
        lambda_high=20.0
    )
    assert 0.1 < optimal_lambda < 1.0
    assert error < 1e-6

## Numerical Stability Tests -------------------------------------------------
def test_large_N_execute_stability():
    N = 100
    fact_array = FactorialArray(N)
    result = Execute(0.5, N, fact_array)
    assert abs(result - math.pi) < 1e-8

def test_rising_factorial_precision():
    # Test with large n where precision might suffer
    result = RisingFactorial(0.5, 50)
    # Calculate using log gamma for precision
    expected = math.exp(math.lgamma(0.5 + 50) - math.lgamma(0.5))
    assert abs(result - expected) / expected < 1e-10

## Edge Case Tests -----------------------------------------------------------
def test_Execute_zero_terms():
    fact_array = FactorialArray(0)
    result = Execute(0.5, 0, fact_array)
    assert result == 4.0

def test_Execute_single_term():
    fact_array = FactorialArray(1)
    result = Execute(0.5, 1, fact_array)
    term = 1.0 * (1/(1+0.5) - 4/(2*1+1)) * ((2*1+1)**2/(4*(1+0.5)) - 1)
    assert result == pytest.approx(4.0 + term)

def test_find_optimal_lambda_small_N():
    optimal_lambda, error = find_optimal_lambda(5)
    assert error > 1e-3  # Should have significant error with few terms

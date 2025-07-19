# July 2025 , by Celestine_1729

# This file contains the functions used in this summer project,
# I tried to write them as clean as possible , and write enough tests
# with enough coverage rate .

import numpy as np
import matplotlib.pyplot as plt
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


@lru_cache(maxsize=None) #TODO: figure out what this is.
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

# This script calculates the Pochhammer symbol and Stirling numbers of the first kind.
#TODO the first step is to write a working script
import numpy as np
import os
import math
from numpy.polynomial import Polynomial


def OneOverFactorial(num):
    if num > 177:
        print("Error : Input is too large to calculate 1/n!. It will cause overflow")
        os.exit()

    index = 1
    product = 1

    while index <= num :
        product = product / index
        index = index + 1

    return product

def StirlingNumberOfFirstKind(n, k):
    number = 0

    if n == k :
        number = 1
    elif n == k-1:
        number = 0.5*n*(n+1)
    elif k==1:
        number = math.factorial(n-1)
    elif (n==0 and k!=0) or (n!=0 and k==0):
        number = 0
    else :
        number = (n-1) * StirlingNumberOfFirstKind(n-1, k) +
        StirlingNumberOfFirstKind(n-1, k-1)

    return number

def Pochhammer(input_n):
    polynomial = np.zeros(input_n + 1)

    for i in range(1, input_n+1):
        polynomial[input_n + 1 - i] = StirlingNumberOfFirstKind(input_n, i)

    poly_handle = Polynomial(polynomial)
    return poly_handle


def FacorialArray(num):
    FactArr = np.zeros(num)

    for i in range(1, num + 1):
        val = OneOverFactorial(i)
        FactArr[i] = val

    return FactArr

def PolynomialArray(num):
    Array = np.zeros([num + 1, num + 1])
    Array[1, num+1] = 1

    for i in range(1, num + 1):
        poly = Pochhammer(i)
        Array[i+1][num - i+1:num+1] = poly


def Execute(Lambda, NTerms, Polynomials, Factorials):
    def FirstParenthesis(lambda, n):
        return 1 / (n + lambda) - 4 / (2 * n + 1)

    def SecondParenthesis(lambda, n):
        return (2 * n + 1) ** 2 / (4*(n + lambda)) - n

    for i in range(1, NTerms+1):
        FACT = Factorials[i]
        FirstParenthesisVal = FirstParenthesis(Lambda, i)
        SecondParenthesisVal = SecondParenthesis(Lambda, i)

        polynom = Polynomials[i]
        PochhammerVal =









% Script to find root of the method as a function of lambda

NTerms = 20
RangeStart = 2
RangeEnd = 3
Tolerance = 1e-14


Polynomials = PolynomialArray(NTerms);
Factorials = FactorialArray(NTerms);

ExecuteHandle = @(lambda)(Execute(lambda, NTerms, Polynomials, Factorials) - pi);

RootFindingSteps = Bisection(ExecuteHandle, RangeStart, RangeEnd, Tolerance);


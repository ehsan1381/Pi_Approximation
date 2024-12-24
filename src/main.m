% script to test and debug
% THIS IS NOT PART OF THE MAIN PROGRAM

Nterms = input("Truncation point ");

tic;

% computing approximation error for different values of lambda
LambdaArr = linspace(LRangeStart, LRangeEnd, LArrSize);

Polys = PolynomialArray(Nterms);
Facts = FactorialArray(Nterms);

% for ease of use
ExecuteHandle = @(lambda)(Execute(lambda, Nterms, Polys, Facts));

ErrorArr = zeros([LArrSize, 1]);
ApproxArr = zeros([LArrSize, 1]);

for i = 1:LArrSize
  lambda = LambdaArr(i);
  Approx = ExecuteHandle(lambda);
  ErrorArr(i) = Approx - pi;
  ApproxArr(i) = Approx;
end
toc;

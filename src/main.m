% main file



% global variables and program settings
% LAMBDA = input("Enter value for lambda: ")
% N_TERMS = input("Enter number of terms: ")
% LAMBDA = 2.4
% N_TERMS = 10

ARR_TERMS = zeros([1, N_TERMS]);
% ARR_TERMS = zeros([1, N_TERMS + 1]);
% ARR_TERMS(1) = 4;


% function handles
FirstParenthesis = @(lambda, n)(1 / ( n + lambda ) - 4 /( 2*n +1 ));
SecondParenthesis = @(lambda, n)(( 2*n + 1 )^2 / ( 4*(n + lambda )) - n );

% compute the terms
for i=[1:N_TERMS]
  FACT = OneOverFactorial(i);
  FirstParenthesisVal = FirstParenthesis(LAMBDA, i);
  SecondParenthesisVal = SecondParenthesis(LAMBDA, i);

  polynom = Pochhammer( i );
  PochhammerVal = polyval(polynom, SecondParenthesisVal);

  Product = FACT * FirstParenthesisVal * PochhammerVal;
  ARR_TERMS(i) = Product;
end % for

% compute sum
PI_APPROX = 4 + sum(ARR_TERMS)

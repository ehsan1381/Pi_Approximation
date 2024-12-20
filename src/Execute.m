function [ PI_APPROX ] = Execute(LAMBDA, N_TERMS, Polynomials, Factorials)
  ARR_TERMS = zeros([1, N_TERMS]);

  % function handles
  FirstParenthesis = @(lambda, n)(1 / ( n + lambda ) - 4 /( 2*n +1 ));
  SecondParenthesis = @(lambda, n)(( 2*n + 1 )^2 / ( 4*(n + lambda )) - n );

  % compute the terms
  for i= 1:N_TERMS
    FACT = Factorials(i);
    FirstParenthesisVal = FirstParenthesis(LAMBDA, i);
    SecondParenthesisVal = SecondParenthesis(LAMBDA, i);

    % polynom = Pochhammer( i );
    polynom = Polynomials(i, 1:i+1);
    PochhammerVal = polyval(polynom, SecondParenthesisVal);

    Product = FACT * FirstParenthesisVal * PochhammerVal;
    ARR_TERMS(i) = Product;
  end % for

  % compute sum
  PI_APPROX = 4 + sum(ARR_TERMS);
end % function

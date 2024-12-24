% to prevent computation of polynomials at each iteration of loop bellow
function Array = PolynomialArray(n)
  Array = zeros(n+1);
  Array(1, n+1) = 1;

  for i = 1:n
    poly = Pochhammer(i);
    Array(i+1, n-i+1:n+1) = poly;

  end % for
end % function

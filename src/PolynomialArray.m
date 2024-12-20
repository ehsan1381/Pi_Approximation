% to prevent computation of polynomials at each iteration of loop bellow
function Array = PolynomialArray(n)
  Array = zeros(n);
  for i=[1:n]
    poly = Pochhammer(i);
    Array(i, 1:i+1) = poly;
  end % for
end % function

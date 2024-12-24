% to prevent calculation of OneOverFactorial calues for everu iteration
function [ FactArr ] = FactorialArray( n )
  FactArr = zeros([1, n]);

  for i = 1:n
    val = OneOverFactorial(i);
    FactArr(i) = val;
  end % for
end % function

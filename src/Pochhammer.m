function [ poly_handle ] = Pochhammer( input_n )
  % Compute the pochhammer polynomial for given inputs x and n
  %   Usage : Pochhammer(x, n)
  %       x is of type double and n is integer value (not necessarily of integer type)
  %       Both arguments must be passed. They do not have a default value


  arguments
%    input_x (1, 1) double
    input_n (1, 1) double
  end

  % The constant term must be left zero
  polynomial = zeros([1, input_n+1]);

  for i=[1:input_n]
    polynomial(i) = StirlingNumberOfFirstKind(input_n, i);
  end % for

  % poly_handle = @(input_x)(polyval(polynomial, input_x));
  poly_handle = polynomial;
end % function

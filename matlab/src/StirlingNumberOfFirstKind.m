% This function computes sterling numbers of the first kind




function [ number ] = StirlingNumberOfFirstKind(n, k)
    number = 0;

    % check for base values
    if n == k
        number = 1;
    elseif n == k - 1
        number = 0.5*n*(n+1);
    elseif k == 1
        number = factorial(n-1);
    elseif (n==0 && k~=0) || (n~=0 && k==0)
        number = 0;
    else
        number = (n-1) * StirlingNumberOfFirstKind( n - 1, k) + StirlingNumberOfFirstKind( n - 1, k - 1);
    end % if n==0 && k~=0

    return







end % function

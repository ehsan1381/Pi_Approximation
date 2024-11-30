% This function computes sterling numbers of the first kind




function [ number ] = SterlingNumberOfFirstKind(n, k)
    number = 0;

    % check for base values
    if n==k
        number = 1;
    elseif (n==0 && k~=0) || (n~=0 && k==0)
        number = 0;
    else
        number = (n-1) * SterlingNumberOfFirstKind( n - 1, k) + SterlingNumberOfFirstKind( n - 1, k - 1);
    end % if n==0 && k~=0

    return







end % function

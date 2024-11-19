% This function computes sterling numbers of the first kind




function [ number ] = SterlingNumberOfFirstKind(n, k)
    

    % check for base values
    if n==0 && k~=0
        number = 0;
    elseif n~=0 && k==0
        number = 0;
    elseif n==0 && k==0
        number = 1;
    else
        number = n * SterlingNumberOfFirstKind( n - 1, k) + SterlingNumberOfFirstKind( n - 1, k - 1);
    end % if n==0 && k~=0
    
    return







end % function
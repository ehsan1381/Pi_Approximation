% This function computes sterling numbers of the first kind





function [ number ] = SterlingNumberOfFirstKind(n, k)
    if n==0 && k~=0
        number = 0;
        return 
    elseif n~=0 && k==0
        number = 0;
        return
    
    elseif n==0 && k==0
        number = 1;
        return

    else
        number = n * SterlingNumberOfFirstKind( n - 1, k ) + SterlingNumberOfFirstKind( n - 1, k - 1 );
    end






end % function
% This function calculates the 1/n! at for given n

function [product] = OneOverFactorial(num)

    index = 1;
    product = double(1);

    while index <= num
	    product = product / index;
	    index = index + 1;
    end % while
    
    
end % OneOverFactorial
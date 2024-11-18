% This function calculates the 1/n! at for given n

function [product] = OneOverFactorial(num)

    
    if num > 178
        disp("Error : Input is too large to calculate 1/n!");
        return ;
    end

    index = 1;
    product = double(1);

    while index <= num
	    product = product / index;
	    index = index + 1;
    end % while
    
    
end % OneOverFactorial
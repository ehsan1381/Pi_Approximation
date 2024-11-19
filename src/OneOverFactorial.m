% This function calculates the 1/n! at for given n

function [product] = OneOverFactorial(num)
    % check validity of input arguement
    arguments
        num (1, 1) uint64
    end % arguments
    
    % check feasibility of input given
    % the 177 limit is calculated based on 64bit
    % floating point. For number larger than 177
    % the program division by 178 in the algorithm
    % will cause underflow to zero
    if num > 177
        disp("Error : Input is too large to calculate 1/n!. It will cause overflow");
        
	% exit the program
	return ;
    end

    % set the product and index variables
    index = 1;
    product = double(1);

    % continouos division algorithm
    while index <= num
	    % divide product by the index and store
	    product = product / index;

	    % increment index
	    index = index + 1;

    end % while
    
    
end % OneOverFactorial

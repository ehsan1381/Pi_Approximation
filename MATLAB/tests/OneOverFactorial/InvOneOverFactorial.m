% This function calculates inverse of1/n! at for given n

function [OutNum, Data] = InvOneOverFactorial(ApproximateValue, num)
    % check validity of arguements
    arguments
        ApproximateValue (1, 1) double
        num (1, 1) double
    end % arguments
    
    % define an array to store the process
    Data = zeros([num + 1, 1]);

    % set the initial element as the given input
    Data(1) = ApproximateValue;
    
    % set an index variable for the loop
    index = 1;

    % set outnum to approximated value 
    OutNum = ApproximateValue;

    % iterative loop to compute products
    % starting from n-1 going back to 1
    while index <= num

	% compute the product
	% the index+1 is an integer operation
	% thus computed first to avoid possible error
	% accumulation
        OutNum = OutNum * (num - (index + 1));
        
	% Add the computed value to the array
	Data(index+1)  = OutNum;

	% increment index
	index = index + 1;
    end % while
    
    
end % InvOneOverFactorial

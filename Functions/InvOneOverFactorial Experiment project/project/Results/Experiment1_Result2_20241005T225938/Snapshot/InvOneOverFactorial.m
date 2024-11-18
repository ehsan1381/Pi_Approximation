% This function calculates the 1/n! at for given n

function [OutNum] = InvOneOverFactorial(ApproximateValue, num)
    arguments
        ApproximateValue (1, 1) double
        num (1, 1) double
    end % arguments

    index = 1;
    OutNum = ApproximateValue;

    while index <= num
	    OutNum = OutNum * (num - index + 1);
	    index = index + 1;
    end % while
    
    
end % InvOneOverFactorial
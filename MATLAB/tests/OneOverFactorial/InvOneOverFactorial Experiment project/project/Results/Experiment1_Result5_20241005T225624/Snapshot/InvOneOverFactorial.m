% This function calculates the 1/n! at for given n

function [OutNum, Data] = InvOneOverFactorial(ApproximateValue, num)
    arguments
        ApproximateValue (1, 1) double
        num (1, 1) double
    end % arguments
    
    Data = zeros([num, 1]);
    Data(1) = ApproximateValue;
    index = 1;
    OutNum = ApproximateValue;

    while index <= num
	    OutNum = OutNum * (num - index + 1)
        Data(index+1)  = [OutNum];
	    index = index + 1
    end % while
    
    
end % InvOneOverFactorial
% Experiment function

function [ApproxInv] = ExperimentFunction(n)
    Approx = OneOverFactorial(n.n);
    ApproxInv = InvOneOverFactorial(Approx, n.n);


end % experiment function
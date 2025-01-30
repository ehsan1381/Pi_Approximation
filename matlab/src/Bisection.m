function [ Approximation ] = Bisection(f, Start, End, TOL)

  % This N_0 is computed using the error bound formula for bisection method
  N_0 = ceil( ( log( End - Start ) - log( TOL ) ) / log( 2 ) );

  % to prevent computatio from happening in case requested precision is too high
  if 2 * eps > TOL
    error('%s is less then twice the computer epsilon. Bisection method cannot produce such accurate results', num2str(TOL, 15));
  end

  FA = f(Start);
  LoopCounter = 1;
  Approximation = 0;

  % loop capped at max number of steps required for algorithm to produce the approximation
  while LoopCounter <= N_0
    Approximation = (Start + End) / 2;

    % in case start, end or midpoint are good approximations
    FP = f(Approximation);
    LoopCounter = LoopCounter + 1;

    if FA * FP > 0
      Start = Approximation;
      FA = FP;
    else
      End=Approximation;
    end

  end
end

% test parameters
f = @(x)(x.^3 + 4*x.^2 - 10);
intervalStart = 1;
intervalEnd = 2;
tolerance = 1e-3;
correctRoot = 1.365230013;

% preconditions
% This N_0 is computed using the error bound formula for bisection method
N_0 = ceil( ( log( intervalEnd - intervalStart ) - log( tolerance ) ) / log( 2 ) );
assert(N_0 < 14, 'Failure on N_0');


%% Step 1
Approximation = Bisection(f, intervalStart, intervalEnd, tolerance * 1e2);
assert(abs(Approximation - correctRoot) <= tolerance * 1e2, 'Failure on step 1');


%% Step 2
Approximation = Bisection(f, intervalStart, intervalEnd, tolerance * 1e1);
assert(abs(Approximation - correctRoot) <= tolerance * 1e1, 'Failure on step 2');

%% Step 3
Approximation = Bisection(f, intervalStart, intervalEnd, tolerance);
assert(abs(Approximation - correctRoot) <= tolerance, 'Failure on step 3');

%% Step 4
Approximation = Bisection(f, intervalStart, intervalEnd, tolerance * 1e-1);
assert(abs(Approximation - correctRoot) <= tolerance * 1e-1, 'Failure on step 4');

%% Step 5
Approximation = Bisection(f, intervalStart, intervalEnd, 1e-9);
assert(abs(Approximation - correctRoot) <= 1e-9, 'Failure on step 5');

% test parameters
Case3 = 1/6;
Case5 = 1/120;
Case10 =2.755731922398589e-07;
Case50 = 3.287949416633158e-65;
Case100 = 1.071510288125468e-158;
Case170 = 1.377900967791772e-307;


%% Case 3
Approx = OneOverFactorial(3);
assert(abs(Approx - Case3) <= 1e-15);

%% Case 5
Approx = OneOverFactorial(5);
assert(abs(Approx - Case5) <= 1e-15);

%% Case 10
Approx = OneOverFactorial(10);
assert(abs(Approx - Case10) <= 1e-15);

%% Case 50
Approx = OneOverFactorial(50);
assert(abs(Approx - Case50) <= 1e-15);

%% Case 100
Approx = OneOverFactorial(100);
assert(abs(Approx - Case100) <= 1e-15);

%% Case 170
Approx = OneOverFactorial(170);
assert(abs(Approx - Case170) <= 1e-15);

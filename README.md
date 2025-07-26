# Idea
A few months ago I came across a paper on topic of string theory. The
researcheers accidentally found a new way of approximating pi in their work. The
method is interesting to me for two reasons. First it contains a lambda
parameter which when its limit is take to infinity, the series will converge to
Medhava seres. Possibly the worse method of approximating pi. Because the
approximation error is a function of this lambda, I want to find optimal
value/values for this parameter. Second is that the series contains every
headache for numerical analysis work. Large numbers, small numbers, possibility
for overflow and underflow, rounding errors, etc. . I want to use this as a
practice problem both for programming and the theoretical side of things.


# Roadmap
~First step is to prepare simple working version of the program in MATLAB. The
modify it to make it a robust code. Optimize the algorithms wherever possible.~

~add python version~

~The second step is to translate that final code to C and again optimize for
performance and precision.~

note: the result for python and C is identical : Error=4.1007197638e-12


In the third step I will add ability to use 128bit floats in the C program

And lastly will modify the program to run in parallel.

As I said this is mostly an exercise. I want to expand on it as much as I can.
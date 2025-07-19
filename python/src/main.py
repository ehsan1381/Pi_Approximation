# July 2025 , by Celestine_1729
#
# I forked this repo from a friend, 
# It tries to calculate or more specificly, approximate the PI number , 
# using one of the worst methods available, because the method is new,
# and we want to see how far we can push it and then maybe , compare it online.

import functions
import matplotlib.pyplot as plt


# Test optimization for different term counts
if __name__ == '__main__':
    term_counts = [88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100]
    results = {}
    
    for N in term_counts:
        lambda_opt, error = functions.find_optimal_lambda(N)
        results[N] = (lambda_opt, error)
        print(f"N={N}: Optimal λ={lambda_opt:.12f}, Error={error:.10e}")

        
    
    # Plot results
    lambdas = [results[N][0] for N in term_counts]
    errors = [results[N][1] for N in term_counts]
    
    
    plt.figure(figsize=(10, 5))
    
    plt.subplot(1, 2, 1)
    plt.plot(term_counts, lambdas, 'o-')
    plt.xlabel('Number of Terms (N)')
    plt.ylabel('Optimal λ')
    plt.title('Optimal λ vs Term Count')
    
    plt.subplot(1, 2, 2)
    plt.semilogy(term_counts, errors, 's-')
    plt.xlabel('Number of Terms (N)')
    plt.ylabel('Error')
    plt.title('Approximation Error at Optimal λ')
    
    plt.tight_layout()
    plt.savefig('lambda_optimization.png')
    plt.show()
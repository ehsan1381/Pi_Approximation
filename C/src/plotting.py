import numpy as np
import matplotlib.pyplot as plt
import os

# Read data from file
data = np.loadtxt('lambda_optimization_data.txt')
term_counts = data[:, 0]
lambdas = data[:, 1]
errors = data[:, 2]

# Create the plots
plt.figure(figsize=(12, 6))

# Plot 1: Optimal λ vs Term Count
plt.subplot(1, 2, 1)
plt.plot(term_counts, lambdas, 'o-', color='royalblue')
plt.xlabel('Number of Terms (N)')
plt.ylabel('Optimal λ')
plt.title('Optimal λ vs Term Count')
plt.grid(True, alpha=0.3)

# Plot 2: Error vs Term Count (log scale)
plt.subplot(1, 2, 2)
plt.semilogy(term_counts, errors, 's-', color='crimson')
plt.xlabel('Number of Terms (N)')
plt.ylabel('Error (log scale)')
plt.title('Approximation Error at Optimal λ')
plt.grid(True, which='both', alpha=0.3)

# Add some statistics
plt.figtext(0.5, 0.01, 
            f"Min error: {min(errors):.2e} at N={term_counts[np.argmin(errors)]} | "
            f"Max error: {max(errors):.2e} at N={term_counts[np.argmax(errors)]}",
            ha='center', fontsize=10, bbox=dict(facecolor='lightyellow', alpha=0.5))


plt.savefig('lambda_optimization_analysis.png', dpi=150)
plt.show()

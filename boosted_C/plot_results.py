import numpy as np
import matplotlib.pyplot as plt
import os

# Read data from file with high precision
with open('lambda_optimization_data.txt', 'r') as f:
    data_lines = f.readlines()

# Parse data manually for high precision
term_counts = []
lambdas = []
errors = []

for line in data_lines:
    parts = line.split()
    term_counts.append(int(parts[0]))
    lambdas.append(float(parts[1]))
    errors.append(float(parts[2]))

term_counts = np.array(term_counts)
lambdas = np.array(lambdas)
errors = np.array(errors)

# Create the plots
plt.figure(figsize=(12, 6))

# Plot 1: Optimal λ vs Term Count
plt.subplot(1, 2, 1)
plt.plot(term_counts, lambdas, 'o-', color='royalblue')
plt.xlabel('Number of Terms (N)')
plt.ylabel('Optimal λ')
plt.title('Optimal λ vs Term Count (Quad Precision)')
plt.grid(True, alpha=0.3)

# Plot 2: Error vs Term Count (log scale)
plt.subplot(1, 2, 2)
plt.semilogy(term_counts, errors, 's-', color='crimson')
plt.xlabel('Number of Terms (N)')
plt.ylabel('Error (log scale)')
plt.title('Quad-Precision Error at Optimal λ')
plt.grid(True, which='both', alpha=0.3)

# Add statistics
min_err = np.min(errors)
max_err = np.max(errors)
min_n = term_counts[np.argmin(errors)]
max_n = term_counts[np.argmax(errors)]

plt.figtext(0.5, 0.01, 
            f"Min error: {min_err:.5e} at N={min_n} | "
            f"Max error: {max_err:.5e} at N={max_n}",
            ha='center', fontsize=10, bbox=dict(facecolor='lightyellow', alpha=0.5))

plt.tight_layout(rect=[0, 0.05, 1, 0.95])
plt.savefig('lambda_optimization_analysis_quad.png', dpi=150)
plt.show()
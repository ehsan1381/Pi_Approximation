import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

# Read data from file
with open('lambda_optimization_data_boost.txt', 'r') as f:
    data_lines = f.readlines()

# Parse data
term_counts = []
lambdas = []
errors = []

for line in data_lines:
    parts = line.strip().split()
    if len(parts) < 3:
        continue
        
    term_counts.append(int(parts[0]))
    lambdas.append(float(parts[1]))
    errors.append(float(parts[2]))

term_counts = np.array(term_counts)
lambdas = np.array(lambdas)
errors = np.array(errors)

# Create the plots
plt.figure(figsize=(15, 8))

# Plot 1: Optimal λ vs Term Count
plt.subplot(2, 2, 1)
plt.plot(term_counts, lambdas, 'o-', color='royalblue', markersize=6)
plt.xlabel('Number of Terms (N)')
plt.ylabel('Optimal λ')
plt.title('Optimal λ vs Term Count (Boost Multiprecision)')
plt.grid(True, alpha=0.3)

# Plot 2: Error vs Term Count (log scale)
plt.subplot(2, 2, 2)
plt.semilogy(term_counts, errors, 's-', color='crimson', markersize=5)
plt.xlabel('Number of Terms (N)')
plt.ylabel('Error (log scale)')
plt.title('Approximation Error at Optimal λ')
plt.grid(True, which='both', alpha=0.3)

# Plot 3: Convergence Rate
plt.subplot(2, 2, 3)
plt.loglog(term_counts, errors, 'D-', color='darkgreen', markersize=5)
plt.xlabel('Number of Terms (N)')
plt.ylabel('Error (log scale)')
plt.title('Convergence Rate')
plt.grid(True, which='both', alpha=0.3)

# Plot 4: Error vs Lambda
plt.subplot(2, 2, 4)
plt.semilogy(lambdas, errors, 'o-', color='purple', markersize=5)
plt.xlabel('Optimal λ')
plt.ylabel('Error (log scale)')
plt.title('Error vs Optimal λ')
plt.grid(True, which='both', alpha=0.3)

# Add statistics
min_err = np.min(errors)
max_err = np.max(errors)
min_n = term_counts[np.argmin(errors)]
max_n = term_counts[np.argmax(errors)]

plt.figtext(0.5, 0.01, 
            f"Min error: {min_err:.5e} at N={min_n} | "
            f"Max error: {max_err:.5e} at N={max_n} | "
            f"Precision gain: {np.log10(max_err/min_err):.1f} orders of magnitude",
            ha='center', fontsize=10, bbox=dict(facecolor='lightyellow', alpha=0.5))

plt.tight_layout(rect=[0, 0.05, 1, 0.95])
plt.savefig('lambda_optimization_analysis_boost.png', dpi=150, bbox_inches='tight')
plt.show()

# Precision analysis
print("\nPrecision Analysis:")
print(f"Smallest error: {min_err:.5e} at N={min_n}")
print(f"Largest error: {max_err:.5e} at N={max_n}")
print(f"Error reduction from max to min: {max_err/min_err:.1f}x")
print(f"Decimal digits of precision at best point: {-np.log10(min_err):.1f}")
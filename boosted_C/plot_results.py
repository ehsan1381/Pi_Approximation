import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def load_results(precision_mode):
    """Load results based on precision mode"""
    if precision_mode == 0:
        dtype = [('terms', int), ('lambda', float), ('error', float), ('time', float)]
    else:
        # Use object dtype to handle long double strings
        dtype = [('terms', int), ('lambda', object), ('error', object), ('time', float)]
    
    data = np.genfromtxt('results.txt', skip_header=1, dtype=dtype, delimiter='\t')
    
    # Convert long double strings if needed
    if precision_mode == 1:
        terms = data['terms']
        lambdas = np.array([float(x) for x in data['lambda']])
        errors = np.array([float(x) for x in data['error']])
        times = data['time']
        return terms, lambdas, errors, times
    
    return data['terms'], data['lambda'], data['error'], data['time']

def main():
    precision_mode = 1  # 0 = double, 1 = long double
    
    try:
        terms, lambdas, errors, times = load_results(precision_mode)
    except Exception as e:
        print(f"Error loading data: {e}")
        return
    
    # Create plots
    fig = plt.figure(figsize=(18, 12))
    
    # Plot 1: Lambda vs Terms
    ax1 = fig.add_subplot(221)
    ax1.plot(terms, lambdas, 'o-', markersize=6, linewidth=2)
    ax1.set_xlabel('Number of Terms')
    ax1.set_ylabel('Optimal Lambda')
    ax1.set_title('Optimal Lambda vs Term Count')
    ax1.grid(True, alpha=0.3)
    
    # Plot 2: Error vs Terms (log scale)
    ax2 = fig.add_subplot(222)
    ax2.semilogy(terms, errors, 's-', markersize=6, linewidth=2, color='red')
    ax2.set_xlabel('Number of Terms')
    ax2.set_ylabel('Approximation Error (log scale)')
    ax2.set_title('Error vs Term Count')
    ax2.grid(True, which='both', alpha=0.3)
    
    # Plot 3: Computation Time
    ax3 = fig.add_subplot(223)
    ax3.plot(terms, times, 'd-', markersize=6, linewidth=2, color='green')
    ax3.set_xlabel('Number of Terms')
    ax3.set_ylabel('Computation Time (ms)')
    ax3.set_title('Computation Time vs Term Count')
    ax3.grid(True, alpha=0.3)
    
    # Plot 4: 3D Visualization
    ax4 = fig.add_subplot(224, projection='3d')
    sc = ax4.scatter(terms, lambdas, np.log10(errors), c=times, cmap='viridis', s=100)
    ax4.set_xlabel('Number of Terms')
    ax4.set_ylabel('Optimal Lambda')
    ax4.set_zlabel('log10(Error)')
    ax4.set_title('Convergence Analysis')
    fig.colorbar(sc, ax=ax4, label='Time (ms)')
    
    plt.suptitle(f"π Approximation Analysis ({'Long Double' if precision_mode else 'Double'} Precision)", 
                 fontsize=16)
    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.savefig('pi_analysis.png', dpi=200)
    plt.show()
    
    # Print statistics
    min_err_idx = np.argmin(errors)
    max_term_idx = np.argmax(terms)
    print("\n===== ANALYSIS SUMMARY =====")
    print(f"Best precision: {errors[min_err_idx]:.3e} at {terms[min_err_idx]} terms")
    print(f"Max terms computed: {terms[max_term_idx]}")
    print(f"Average time: {np.mean(times):.2f} ms per computation")

if __name__ == "__main__":
    main()
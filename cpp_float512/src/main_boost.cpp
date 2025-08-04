#include "functions_boost.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <boost/format.hpp>

int main() {
    // Test parameters - extended range for higher precision
    std::vector<int> term_counts;
    for (int i = 90; i <= 150; i += 5) {
        term_counts.push_back(i);
    }
    term_counts.push_back(160);
    term_counts.push_back(170);
    term_counts.push_back(180);
    term_counts.push_back(200);

    std::ofstream fp("lambda_optimization_data_boost.txt");
    if (!fp) {
        std::cerr << "Failed to open file" << std::endl;
        return EXIT_FAILURE;
    }

    // Set full precision output
    fp << std::setprecision(50);
    std::cout << std::setprecision(50);

    // Compute and save results
    for (size_t i = 0; i < term_counts.size(); i++) {
        int N = term_counts[i];
        mp_float result[2];
        find_optimal_lambda(N, 0.1, 1.0, 1e-100, result);
        
        // Format output with boost::format for better control
        std::string output = boost::str(boost::format("N=%d: Optimal λ=%.50f, Error=%.10e") 
                             % N % result[0] % result[1]);
        
        std::cout << output << std::endl;
        fp << N << " " << result[0] << " " << result[1] << std::endl;
    }

    fp.close();
    return EXIT_SUCCESS;
}
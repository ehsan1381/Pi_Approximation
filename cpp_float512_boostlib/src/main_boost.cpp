// main_boost.cpp
//August 2025 , by Clestine1729
// contact: celestine1729@proton.me
// This file is part of the Boost library for high precision calculations.
// It tries to optimize the value of λ for high precision calculations for finding π.
// It provides the main function to execute the optimization of λ for high precision calculations.


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

        // Output using .str() for high precision
        std::cout << "N=" << N
                  << ": Optimal λ=" << result[0].str(50)
                  << ", Error=" << result[1].str(10) << std::endl;
        fp << N << " " << result[0].str(50) << " " << result[1].str(10) << std::endl;
    }

    fp.close();
    return EXIT_SUCCESS;
}
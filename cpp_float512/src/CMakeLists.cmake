cmake_minimum_required(VERSION 3.10)
project(PiApproximationBoost)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost
find_package(Boost 1.71.0 REQUIRED COMPONENTS math_c99)

# Add executable
add_executable(pi_boost 
    main_boost.cpp 
    functions_boost.cpp
)

# Link against Boost
target_link_libraries(pi_boost 
    PRIVATE 
        Boost::boost 
        Boost::math_c99
)

# Set high optimization level
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(pi_boost PRIVATE -O3)
endif()
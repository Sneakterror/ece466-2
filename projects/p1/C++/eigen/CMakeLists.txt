
# Find Eigen
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# Create the library
add_library(eigen_c STATIC eigen_c.cpp)

# Uncomment the line below to build a shared library instead
# add_library(eigen_c SHARED eigen_c.cpp)

# Include directories
target_include_directories(eigen_c PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EIGEN3_INCLUDE_DIR}
)

# Set C++ standard
set_target_properties(eigen_c PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE ON
)

#include <stdio.h>
#include "eigen_c.h"

int main() {
    // Create matrices
    EigenMatrix* A = eigen_create(2, 2);
    EigenMatrix* B = eigen_create(2, 2);

    // Set values
    eigen_set_element(A, 0, 0, 1);
    eigen_set_element(A, 0, 1, 2);
    eigen_set_element(A, 1, 0, 3);
    eigen_set_element(A, 1, 1, 4);

    eigen_set_element(B, 0, 0, 5);
    eigen_set_element(B, 0, 1, 6);
    eigen_set_element(B, 1, 0, 7);
    eigen_set_element(B, 1, 1, 8);

    // Matrix addition
    EigenMatrix* C = eigen_add(A, B);
    
    // Print result
    printf("C[0,0]: %f\n", eigen_get_element(C, 0, 0));
    printf("C[0,1]: %f\n", eigen_get_element(C, 0, 1));
    printf("C[1,0]: %f\n", eigen_get_element(C, 1, 0));
    printf("C[1,1]: %f\n", eigen_get_element(C, 1, 1));

    // Free memory
    eigen_free(A);
    eigen_free(B);
    eigen_free(C);

    return 0;
}

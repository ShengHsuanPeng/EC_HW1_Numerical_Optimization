#include "binary_ga.h"

namespace binary_ga {

double Schwefel_Function(int* bits, individual::ChromoTyp size) {
    int n_of_x = size.n_of_x;
    int x_len = size.x_len;
    int power_of_two[10] = {512, 256, 128, 64, 32, 16, 8, 4, 2, 1};

    double fsch=418.98291*n_of_x;
    for (int j=0; j<n_of_x; j++) {
        int index = j * x_len;
        double x_i=-512;
        for (int k=0;k<x_len;k++) {
            if(*(bits + index + k))
                x_i+=power_of_two[k];
        }
        fsch -= x_i*sin(sqrt(fabs(x_i)));
    }
    return fsch;
}

// only for Schwefel_Function questions
void BinaryGa::Initial(int n_of_x, int x_len) {
    _gene_length = n_of_x*x_len;
    for (int i = 0; i < _population_size; i++)  {
        population[i] = new individual::Individual(n_of_x, x_len, FitnessFn, false);
        population[i+_population_size]
                = new individual::Individual(n_of_x, x_len, FitnessFn, true);
    }
}

} // namespace binary_ga
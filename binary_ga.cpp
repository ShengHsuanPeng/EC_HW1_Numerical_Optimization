#include "binary_ga.h"

namespace binary_ga {

double Schwefel_Function(int* bits, individual::ChromoTyp size) {
    int n_of_x = size.n_of_x;
    int x_len = size.x_len;
    
    double fsch=418.98291*n_of_x;
    for (int j=0; j<n_of_x; j++) {
        int index = j * x_len;
        double x_i=0;
        for (int k=0;k<x_len;k++) {
            x_i+=double(*(bits + index + k))*pow(2, x_len-k-1);
        }
        x_i-=512;
        fsch -= x_i*sin(sqrt(fabs(x_i)));
    }
    return fsch;
}

// only for Schwefel_Function questions
void BinaryGa::Initial(int n_of_x, int x_len) {
    _gene_length = n_of_x*x_len;
    for (int i = 0; i < _population_size; i++)  {
        population[i] = new individual::Individual(n_of_x, x_len, _fitnessFn, false);
        population[i+_population_size]
                = new individual::Individual(n_of_x, x_len, _fitnessFn, true);
        //std::cout << i << std::endl;
        //population[i]->print(Individual::fitness);
    }
}

} // namespace binary_ga
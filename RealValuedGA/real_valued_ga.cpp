#include "real_valued_ga.h"

namespace real_valued_ga {

double Schwefel_Function(double* bits, individual::ChromoTyp size) {
    int n_of_x = size.n_of_x;
    
    double fsch=418.98291*n_of_x;
    for (int j=0; j<n_of_x; j++) {
        fsch -= (*(bits + j))*sin(sqrt(fabs(*(bits + j))));
    }
    return fsch;
}

// only for Schwefel_Function questions
void RealValuedGa::Initial(int n_of_x) {
    _gene_length = n_of_x;
    for (int i = 0; i < _population_size; i++)  {
        population[i] = new individual::Individual(n_of_x, _fitnessFn, false);
        population[i+_population_size]
                = new individual::Individual(n_of_x, _fitnessFn, true);
    }
}

} // namespace real_valued_ga
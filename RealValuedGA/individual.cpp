#include "individual.h"

#include <iomanip>

namespace individual {

Individual::Individual(int n_of_x, double (*fitness_fn)(double *, int), bool child) {
    gene_size = n_of_x;
    fitnessFN = fitness_fn;
    bits = new double[n_of_x];
    double value = 1023.0/(double)RAND_MAX;
    for (int i = 0; i < n_of_x; i++) {
        if(child == false)
            *(bits + i) = (rand()*value-512);
        else
            *(bits + i) = 0.0;
    }
    
    fitness = fitnessFN(bits, gene_size);
}
void Individual::CalcFitness() {
    fitness = fitnessFN(bits, gene_size);
}
} // namespace individual
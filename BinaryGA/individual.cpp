#include "individual.h"

#include <iomanip>

namespace individual {

Individual::Individual(int n_of_x, int x_len, double (*fitness_fn)(int *, ChromoTyp), bool child) {
    gene_size = {n_of_x, x_len};
    fitnessFN = fitness_fn;
    int total_len = n_of_x * x_len;
    bits = new int[total_len];
    double threshold = 0.5 * (double)RAND_MAX;
    for (int i = 0; i < total_len; i++) {
        if(child == false)
            *(bits + i) = (rand() >= threshold) ? 1 : 0;
        else
            *(bits + i) = 0;
    }
    
    fitness = fitnessFN(bits, gene_size);
}
void Individual::CalcFitness() {
    fitness = fitnessFN(bits, gene_size);
}
} // namespace individual
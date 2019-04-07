#ifndef BINARY_GA_H_
#define BINARY_GA_H_

#include "genetic_algorithm.h"

namespace binary_ga {

double Schwefel_Function(int *bits, individual::ChromoTyp size);

class BinaryGa: public genetic_algorithm::GeneticAlgorithm {
    public:
        BinaryGa(int population_size, 
                double (*fitnessFn)(int *, individual::ChromoTyp))
        : GeneticAlgorithm(population_size, fitnessFn) {}
        void Initial(int n_of_x, int x_len);
        
}; // class BinaryGa: public genetic_algorithm::GeneticAlgorithm

} // namespace binary_ga
#endif // BINARY_GA_H_
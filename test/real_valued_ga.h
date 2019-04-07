#ifndef REAL_VALUED_GA_H_
#define REAL_VALUED_GA_H_

#include "genetic_algorithm.h"

namespace real_valued_ga {

double Schwefel_Function(int *bits, individual::ChromoTyp size);

class RealValuedGa: public genetic_algorithm::GeneticAlgorithm {
    public:
        RealValuedGa(int population_size, 
                double (*fitnessFn)(int *, individual::ChromoTyp))
        : GeneticAlgorithm(population_size, fitnessFn) {}
        void Initial(int n_of_x);
        
}; // class RealValuedGa: public genetic_algorithm::GeneticAlgorithm

} // namespace real_valued_ga
#endif // REAL_VALUED_GA_H_
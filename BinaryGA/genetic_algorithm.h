#ifndef GENETIC_ALGORITHM_H_
#define GENETIC_ALGORITHM_H_

#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

#include "individual.h"
#include "utility.h"

namespace genetic_algorithm {

typedef enum {
    two_pt,
    uniform
} CrossoverMethod;

// GeneticAlgorithm
class GeneticAlgorithm {
    private:
        void TwoPtCrossover(double p_c, int n_tnmt);
        void UniformCrossover(double p_c, int n_tnmt);
        individual::Individual* TnmtSelection(int n_tnmt);

      protected:
        std::vector<individual::Individual*> population;
        int _population_size;
        int _gene_length;
        double (*FitnessFn)(int *, individual::ChromoTyp);

    public:
        double max_fitness;
        GeneticAlgorithm(int, double (*fitnessFn)(int *, individual::ChromoTyp));
        ~GeneticAlgorithm();
        void Initial(int len);
        void Selection();
        void Crossover(CrossoverMethod, double p_c, int n_tnmt);
        void Mutation(double p_m);
        void Survivor();
};

} // namespace genetic_algorithm 

#endif // GENETIC_ALGORITHM_H_
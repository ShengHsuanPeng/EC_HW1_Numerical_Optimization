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
    uniform,
    whole_arithmetic
} CrossoverMethod;

// GeneticAlgorithm
class GeneticAlgorithm {
    private:
        void TwoPtCrossover(double p_c, int n_tnmt);
        void UniformCrossover(double p_c, int n_tnmt);
        void WholeArithmeticCrossover(double p_c, int n_tnmt, double a);
        individual::Individual* TnmtSelection(int n_tnmt);

      protected:
        std::vector<individual::Individual*> population;
        int _population_size;
        int _gene_length;
        double (*_fitnessFn)(double *, int);

    public:
        double max_fitness;
        GeneticAlgorithm(int, double (*fitnessFn)(double *, int));
        ~GeneticAlgorithm();
        void Initial(int len);
        void Selection();
        void Crossover(CrossoverMethod, double p_c, int n_tnmt);
        void Crossover(CrossoverMethod, double p_c, int n_tnmt, double a);
        void Mutation(double p_m);
        void Survivor();
};

} // namespace genetic_algorithm 

#endif // GENETIC_ALGORITHM_H_